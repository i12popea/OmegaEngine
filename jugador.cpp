#include "jugador.hpp"

using namespace std;
using namespace ed;

namespace ed
{

Jugador & Jugador::operator = (Jugador const &jugador)
{
	if(this != &jugador)
	{
		_camara = jugador._camara;
		_posicionInicial = jugador._posicionInicial;
		//_arma = jugador._arma;
		_salud = jugador._salud;
		_armadura = jugador._armadura;
		_velocidadJugador = jugador._velocidadJugador;
		_salto = jugador._salto;
		_agachado = jugador._agachado;
		//_sonidoSalto = jugador._sonidoSalto;
		_tiempo = jugador._tiempo;
		_impulsoInicial = jugador._impulsoInicial;
		_bounding = jugador._bounding;
		_boundingDePie = jugador._boundingDePie;
		_boundingAgachado = jugador._boundingAgachado;
		_antesDeColision = jugador._antesDeColision;
		_despuesDeColision = jugador._despuesDeColision;
	}
	return *this;
}

void Jugador::MostrarArma()
{
	_arma.DibujarArma();
}

void Jugador::SaludDanada(int cantidad)
{
	_salud = _salud - cantidad;
}

void Jugador::SaludRegenerada()
{
	//Iniciamos una semilla aleatoria
	srand(time(NULL));
	//Escogemos una cantidad entre 10 y 20
	int cantidad = 10 + ( rand() % ( 20 - 10 + 1 ) );
	if(_salud + cantidad > 100)
		_salud = 100;
	else
		_salud = _salud + cantidad;
}

void Jugador::ActualizarPosicion()
{
	vector3d posicion(_camara.getVector().getX(), _camara.getVector().getY() - _bounding.getAltura(), _camara.getVector().getZ());
	_posicion = vector3d(posicion.getX(), posicion.getY() - _bounding.getAltura(), posicion.getZ());
	_bounding.setVector3d(posicion);
	_boundingDePie.setVector3d(posicion);
	vector3d agachado(posicion.getX(), posicion.getY() - _boundingAgachado.getAltura(), posicion.getZ());
	_boundingAgachado.setVector3d(posicion);
}

void Jugador::ColisionPersonaje(vector<Box> &boxes, vector<Esfera> &esferas, vector<Octree*> &objetoOctree, vector<TipoObjeto> &tipoObjeto, vector<Objeto> &objetos, vector<vector3d> &posicion, vector<float> &grados, vector<vector3d> &rotacion, vector<vector3d> &escalado)
{
	bool colision = false;
	bool suelo, techo, pared;
	float diferenciaX, diferenciaZ;
// --------------------------------------------------------------------------------------------------------
	//Colision del personaje con objetos formados por Boxes
	for(unsigned int i = 0; i < boxes.size(); i++)
	{
		if(ColisionCilindroOcteto(boxes[i], _bounding, suelo, techo, pared, diferenciaX, diferenciaZ))
		{
			if(tipoObjeto[i] == BOTIQUIN && _salud < 100)
			{
				objetos.erase(objetos.begin() + i);
				tipoObjeto.erase(tipoObjeto.begin() + i);
				boxes.erase(boxes.begin() + i);
				posicion.erase(posicion.begin() + i);
				grados.erase(grados.begin() + i); rotacion.erase(rotacion.begin() + i);
				escalado.erase(escalado.begin() + i);
				SaludRegenerada();
			}
			if(tipoObjeto[i] == MUNICION)
			{
				objetos.erase(objetos.begin() + i);
				tipoObjeto.erase(tipoObjeto.begin() + i);
				boxes.erase(boxes.begin() + i);
				posicion.erase(posicion.begin() + i);
				grados.erase(grados.begin() + i); rotacion.erase(rotacion.begin() + i);
				escalado.erase(escalado.begin() + i);
				_arma.AumentarMunicion();
			}

			if(tipoObjeto[i] != BOTIQUIN && tipoObjeto[i] != MUNICION)
			{
				colision = true;
				vector3d auxiliar = vector3d(_bounding.getVector3d().getX(), _bounding.getVector3d().getY() + _bounding.getAltura(), _bounding.getVector3d().getZ());	//Guardamos en un auxiliar la posicion del jugador

				ReaccionCilindroOcteto(auxiliar, suelo, techo, pared, boxes[i], _bounding, diferenciaX, diferenciaZ);

				if((suelo) || (techo))
					_camara.setVector(_camara.getVector().getX(), auxiliar.getY(), _camara.getVector().getZ());

				if(pared)
					_camara.setVector(auxiliar.getX(), _camara.getVector().getY(), auxiliar.getZ());

				ActualizarPosicion();
				setImpulsoInicial(0.0f);
				setSalto(false);
				_tiempo = 0.0;
			}
		}
	}
	//Colision del personaje con objetos formados por Esferas
	for(unsigned int i = 0; i < esferas.size(); i++)
	{
		if(ColisionCilindroEsfera(esferas[i], _bounding, suelo, techo, pared, diferenciaX, diferenciaZ))
		{
			if(tipoObjeto[boxes.size() + i] == BOTIQUIN)
			{
				objetos.erase(objetos.begin() + boxes.size() + i);
				tipoObjeto.erase(tipoObjeto.begin() + boxes.size() + i);
				esferas.erase(esferas.begin() + i);
				posicion.erase(posicion.begin() + boxes.size() + i);
				grados.erase(grados.begin() + boxes.size() + i); rotacion.erase(rotacion.begin() + boxes.size() + i);
				escalado.erase(escalado.begin() + boxes.size() + i);
				SaludRegenerada();
			}
			if(tipoObjeto[boxes.size() + i] == MUNICION)
			{
				objetos.erase(objetos.begin() + boxes.size() + i);
				tipoObjeto.erase(tipoObjeto.begin() + boxes.size() + i);
				esferas.erase(esferas.begin() + i);
				posicion.erase(posicion.begin() + boxes.size() + i);
				grados.erase(grados.begin() + boxes.size() + i); rotacion.erase(rotacion.begin() + boxes.size() + i);
				escalado.erase(escalado.begin() + boxes.size() + i);
				_arma.AumentarMunicion();
			}

			colision = true;
			vector3d auxiliar = vector3d(_bounding.getVector3d().getX(), _bounding.getVector3d().getY() + _bounding.getAltura(), _bounding.getVector3d().getZ());	//Guardamos en un auxiliar la posicion del jugador

			ReaccionCilindroEsfera(auxiliar, suelo, techo, pared, esferas[i], _bounding, diferenciaX, diferenciaZ);

			if((suelo) || (techo))
				_camara.setVector(_camara.getVector().getX(), auxiliar.getY(), _camara.getVector().getZ());

			if(pared)
				_camara.setVector(auxiliar.getX(), _camara.getVector().getY(), auxiliar.getZ());

			ActualizarPosicion();
			setImpulsoInicial(0.0f);
			setSalto(false);
			_tiempo = 0.0;
		}
	}
	//Colision del personaje con objetos formados por Octree
	for(unsigned int i = 0; i < objetoOctree.size(); i++)
	{
		Box octetoAuxiliar;
		bool resultado;
		objetoOctree[i]->interseccionOctreeCilindro(_bounding, octetoAuxiliar, suelo, techo, pared, diferenciaX, diferenciaZ, resultado);
		if(resultado)
		//if(objetoOctree[i]->interseccionOctreeCilindro(_bounding, octetoAuxiliar, suelo, techo, pared, diferenciaX, diferenciaZ))
		{
//cout << "colision por octree\n";
			if(tipoObjeto[boxes.size() + esferas.size() + i] == BOTIQUIN)
			{
				objetos.erase(objetos.begin() + boxes.size() + esferas.size() + i);
				tipoObjeto.erase(tipoObjeto.begin() + boxes.size() + esferas.size() + i);
				objetoOctree.erase(objetoOctree.begin() + i);
				posicion.erase(posicion.begin() + boxes.size() + esferas.size() + i);
				grados.erase(grados.begin() + boxes.size() + esferas.size() + i); rotacion.erase(rotacion.begin() + boxes.size() + esferas.size() + i);
				escalado.erase(escalado.begin() + boxes.size() + esferas.size() + i);
				SaludRegenerada();
			}
			if(tipoObjeto[boxes.size() + esferas.size() + i] == MUNICION)
			{
				objetos.erase(objetos.begin() + boxes.size() + esferas.size() + i);
				tipoObjeto.erase(tipoObjeto.begin() + boxes.size() + esferas.size() + i);
				objetoOctree.erase(objetoOctree.begin() + i);
				posicion.erase(posicion.begin() + boxes.size() + esferas.size() + i);
				grados.erase(grados.begin() + boxes.size() + esferas.size() + i); rotacion.erase(rotacion.begin() + boxes.size() + esferas.size() + i);
				escalado.erase(escalado.begin() + boxes.size() + esferas.size() + i);
				_arma.AumentarMunicion();
			}

			colision = true;
			vector3d auxiliar = vector3d(_bounding.getVector3d().getX(), _bounding.getVector3d().getY() + _bounding.getAltura(), _bounding.getVector3d().getZ());	//Guardamos en un auxiliar la posicion del jugador

			ReaccionCilindroOcteto(auxiliar, suelo, techo, pared, octetoAuxiliar, _bounding, diferenciaX, diferenciaZ);

			if((suelo) || (techo))
				_camara.setVector(_camara.getVector().getX(), auxiliar.getY(), _camara.getVector().getZ());

			if(pared)
				_camara.setVector(auxiliar.getX(), _camara.getVector().getY(), auxiliar.getZ());

			ActualizarPosicion();
			setImpulsoInicial(0.0f);
			setSalto(false);
			_tiempo = 0.0;

// ---------------------------------------------------------------

			/*if(tipoObjeto[i] != BOTIQUIN && tipoObjeto[i] != MUNICION)
			{
				colision = true;
				vector3d auxiliar = vector3d(_bounding.getVector3d().getX(), _bounding.getVector3d().getY() + _bounding.getAltura(), _bounding.getVector3d().getZ());	//Guardamos en un auxiliar la posicion del jugador

				ReaccionCilindroOcteto(auxiliar, suelo, techo, pared, octetoAuxiliar, _bounding, diferenciaX, diferenciaZ);

				if((suelo) || (techo))
					_camara.setVector(_camara.getVector().getX(), auxiliar.getY(), _camara.getVector().getZ());

				if(pared)
					_camara.setVector(auxiliar.getX(), _camara.getVector().getY(), auxiliar.getZ());

				ActualizarPosicion();
				setImpulsoInicial(0.0f);
				setSalto(false);
				_tiempo = 0.0;
			}*/
		}
	}

	if(colision)
	{
		_despuesDeColision = _bounding.getVector3d().getY();

		if(_antesDeColision - _despuesDeColision >= 12 && _antesDeColision - _despuesDeColision < 13)
			SaludDanada(5);
		else if(_antesDeColision - _despuesDeColision >= 13 && _antesDeColision - _despuesDeColision < 19)
			SaludDanada(10);
		else if(_antesDeColision - _despuesDeColision >= 19 && _antesDeColision - _despuesDeColision < 26)
			SaludDanada(15);
		else if(_antesDeColision - _despuesDeColision >= 26 && _antesDeColision - _despuesDeColision < 32)
			SaludDanada(22);
		else if(_antesDeColision - _despuesDeColision >= 32 && _antesDeColision - _despuesDeColision < 38)
			SaludDanada(30);
		else if(_antesDeColision - _despuesDeColision >= 38 && _antesDeColision - _despuesDeColision < 44)
			SaludDanada(45);
		else if(_antesDeColision - _despuesDeColision >= 44 && _antesDeColision - _despuesDeColision < 50)
			SaludDanada(55);
		else if(_antesDeColision - _despuesDeColision >= 50 && _antesDeColision - _despuesDeColision < 56)
			SaludDanada(65);
		else if(_antesDeColision - _despuesDeColision >= 56 && _antesDeColision - _despuesDeColision < 62)
			SaludDanada(80);
		else if(_antesDeColision - _despuesDeColision >= 62)
			SaludDanada(100);
		else{}
		_antesDeColision = _bounding.getVector3d().getY();
	}
	if(!colision)
	{
		float nuevoY;
		if(_salto)
		{
			nuevoY = CaidaLibre(_tiempo, getImpulsoInicial(), 9.8, _posicionInicial);
			_camara.setVector(_camara.getVector().getX(), _posicionInicial + nuevoY, _camara.getVector().getZ());
			if(_camara.getVector().getY() - _bounding.getAltura() > _antesDeColision)
				_antesDeColision = _camara.getVector().getY();
		}
		else
		{
			float posInicial = _camara.getVector().getY();
			nuevoY = CaidaLibre(_tiempo, getImpulsoInicial(), 9.8, posInicial);
			_camara.setVector(_camara.getVector().getX(), posInicial + nuevoY, _camara.getVector().getZ());
			if(_camara.getVector().getY() - _bounding.getAltura() > _antesDeColision)
				_antesDeColision = _camara.getVector().getY();
		}
		float frames = 0.05;//CapturaFrames();	//Antes era 0.001
		//frames = 0.05;
		//float frames = 0.0005;//CapturaFrames();	//Antes era 0.001
		//float frames = 0.0002;//CapturaFrames();	//Antes era 0.001
		_tiempo = _tiempo + frames;
		ActualizarPosicion();
	}
// -----------------------------------------------------------------------------------------------------

	//Colision de la municion disparada del jugador contra los objetos del escenario
	for(unsigned int i = 0; i < _arma.getMunicionDisparada()->size(); i++)
	{
		Esfera esfera(_arma.getMunicionDisparada(i).getPosicion(), 0.2);

		for(unsigned int j = 0; j < boxes.size(); j++)
		{
			if(interseccion(esfera, boxes[j]))
			{
				if(tipoObjeto[j] == DESTRUCTIBLE)
				{
					objetos.erase(objetos.begin() + j);
					tipoObjeto.erase(tipoObjeto.begin() + j);
					boxes.erase(boxes.begin() + j);
					posicion.erase(posicion.begin() + j);
					grados.erase(grados.begin() + j); rotacion.erase(rotacion.begin() + j);
					escalado.erase(escalado.begin() + j);
				}

				Sonido explosion;
				explosion.setFichero("sonidos/bazooka.wav");
				alGetError();
				explosion.leerFichero();
				explosion.reproducirSonido();
				_arma.getMunicionDisparada()->erase(_arma.getMunicionDisparada()->begin() + i);
			}
		}
		for(unsigned int j = 0; j < esferas.size(); j++)
		{
			if(interseccion(esfera, esferas[j]))
			{
				if(tipoObjeto[boxes.size() + j] == DESTRUCTIBLE)
				{
					objetos.erase(objetos.begin() + boxes.size() + j);
					tipoObjeto.erase(tipoObjeto.begin() + boxes.size() + j);
					esferas.erase(esferas.begin() + j);
					posicion.erase(posicion.begin() + boxes.size() + j);
					grados.erase(grados.begin() + boxes.size() + j); rotacion.erase(rotacion.begin() + boxes.size() + j);
					escalado.erase(escalado.begin() + boxes.size() + j);
				}

				Sonido explosion;
				explosion.setFichero("sonidos/bazooka.wav");
				alGetError();
				explosion.leerFichero();
				explosion.reproducirSonido();
				_arma.getMunicionDisparada()->erase(_arma.getMunicionDisparada()->begin() + i);
			}
		}
		for(unsigned int j = 0; j < objetoOctree.size(); j++)
		{
			Box octeto(objetoOctree[j]->getCentro(), objetoOctree[j]->getTamano().getY(), objetoOctree[j]->getTamano().getZ(), objetoOctree[j]->getTamano().getX());
			if(interseccion(esfera, octeto))
			{
				if(tipoObjeto[boxes.size() + esferas.size() + j] == DESTRUCTIBLE)
				{
					objetos.erase(objetos.begin() + boxes.size() + esferas.size() + j);
					tipoObjeto.erase(tipoObjeto.begin() + boxes.size() + esferas.size() + j);
					objetoOctree.erase(objetoOctree.begin() + j);
					posicion.erase(posicion.begin() + boxes.size() + esferas.size() + j);
					grados.erase(grados.begin() + boxes.size() + esferas.size() + j); rotacion.erase(rotacion.begin() + boxes.size() + esferas.size() + j);
					escalado.erase(escalado.begin() + boxes.size() + esferas.size() + j);
				}

				Sonido explosion;
				explosion.setFichero("sonidos/bazooka.wav");
				alGetError();
				explosion.leerFichero();
				explosion.reproducirSonido();
				_arma.getMunicionDisparada()->erase(_arma.getMunicionDisparada()->begin() + i);
			}
		}
	}

	/*for(unsigned int i = 0; i < boxes.size(); i++)
	{
		for(unsigned int j = 0; j < _arma.getMunicionDisparada()->size(); j++)
		{
			Esfera esfera(_arma.getMunicionDisparada(j).getPosicion(), 0.2);
			if(interseccion(esfera, boxes[i]))
			{
				if(tipoObjeto[i] == DESTRUCTIBLE)
				{
					objetos.erase(objetos.begin() + i);
					tipoObjeto.erase(tipoObjeto.begin() + i);
					boxes.erase(boxes.begin() + i);
					posicion.erase(posicion.begin() + i);
					grados.erase(grados.begin() + i); rotacion.erase(rotacion.begin() + i);
					escalado.erase(escalado.begin() + i);
				}

				Sonido explosion;
				explosion.setFichero("sonidos/bazooka.wav");
				alGetError();
				explosion.leerFichero();
				explosion.reproducirSonido();
				_arma.getMunicionDisparada()->erase(_arma.getMunicionDisparada()->begin() + j);
			}
		}
	}
	for(unsigned int i = 0; i < esferas.size(); i++)
	{
		for(unsigned int j = 0; j < _arma.getMunicionDisparada()->size(); j++)
		{
			Esfera esfera(_arma.getMunicionDisparada(j).getPosicion(), 0.2);
			if(interseccion(esfera, esferas[i]))
			{
				if(tipoObjeto[boxes.size() + i] == DESTRUCTIBLE)
				{
					objetos.erase(objetos.begin() + boxes.size() + i);
					tipoObjeto.erase(tipoObjeto.begin() + boxes.size() + i);
					esferas.erase(esferas.begin() + i);
					posicion.erase(posicion.begin() + boxes.size() + i);
					grados.erase(grados.begin() + boxes.size() + i); rotacion.erase(rotacion.begin() + boxes.size() + i);
					escalado.erase(escalado.begin() + boxes.size() + i);
				}

				Sonido explosion;
				explosion.setFichero("sonidos/bazooka.wav");
				alGetError();
				explosion.leerFichero();
				explosion.reproducirSonido();
				_arma.getMunicionDisparada()->erase(_arma.getMunicionDisparada()->begin() + j);
			}
		}
	}
	for(unsigned int i = 0; i < objetoOctree.size(); i++)
	{
		for(unsigned int j = 0; j < _arma.getMunicionDisparada()->size(); j++)
		{
			Esfera esfera(_arma.getMunicionDisparada(j).getPosicion(), 0.2);
			Box octeto(objetoOctree[i]->getCentro(), objetoOctree[i]->getTamano().getY(), objetoOctree[i]->getTamano().getZ(), objetoOctree[i]->getTamano().getX());
			if(interseccion(esfera, octeto))
			{
				if(tipoObjeto[boxes.size() + esferas.size() + i] == DESTRUCTIBLE)
				{
					objetos.erase(objetos.begin() + boxes.size() + esferas.size() + i);
					tipoObjeto.erase(tipoObjeto.begin() + boxes.size() + esferas.size() + i);
					objetoOctree.erase(objetoOctree.begin() + i);
					posicion.erase(posicion.begin() + boxes.size() + esferas.size() + i);
					grados.erase(grados.begin() + boxes.size() + esferas.size() + i); rotacion.erase(rotacion.begin() + boxes.size() + esferas.size() + i);
					escalado.erase(escalado.begin() + boxes.size() + esferas.size() + i);
				}

				Sonido explosion;
				explosion.setFichero("sonidos/bazooka.wav");
				alGetError();
				explosion.leerFichero();
				explosion.reproducirSonido();
				_arma.getMunicionDisparada()->erase(_arma.getMunicionDisparada()->begin() + j);
			}
		}
	}*/
}

void Jugador::Salto()
{
	if(!_salto)
	{
		//_sonidoSalto.listener(_camara.getVector());
		_sonidoSalto.setFichero("sonidos/jump1.wav");
		alGetError();
		_sonidoSalto.leerFichero();
		_sonidoSalto.reproducirSonido();
	//	_impulsoInicial = 0;
		_impulsoInicial = 6.5;	//Antes estaba a 13 y daba unos saltos enormes



//		float alturaMaxima = (13*13)/(2*9.8);	//Pongo 13 porque era la velocidad de impulso para un salto
//		_posicionInicial = _camara.getVector().getY();
		_posicionInicial = _camara.getVector().getY() + 0.75;
//cout << _posicionInicial << endl;
		_camara.setVector(_camara.getVector().getX(), _camara.getVector().getY() + 0.75, _camara.getVector().getZ());
		vector3d posicionAuxiliar(_bounding.getVector3d().getX(), _bounding.getVector3d().getY() + 0.75, _bounding.getVector3d().getZ());
		_bounding = Cilindro(posicionAuxiliar, _bounding.getAltura(),  _bounding.getRadio());
		_salto = true;
	}
}

void Jugador::Agacharse()
{
	if(!_agachado)
	{
		/*_camara.setVector(_camara.getVector().getX(), _camara.getVector().getY() - _boundingDePie.getAltura(), _camara.getVector().getZ());
		vector3d posicionAuxiliar(_bounding.getVector3d().getX(), _bounding.getVector3d().getY() - _boundingDePie.getAltura(), _bounding.getVector3d().getZ());
		_bounding = Cilindro(posicionAuxiliar, _bounding.getAltura(), _bounding.getRadio());*/

		/*_camara.setVector(0, 4, 0);
		_boundingDePie = Cilindro(vector3d(0, 2, 0), 2, 1);*/
//		_camara.setVector(_camara.getVector().getX(), _boundingDePie.getVector3d().getY() + _boundingDePie.getAltura(), _camara.getVector().getZ());
		//_boundingDePie = Cilindro(vector3d(_camara.getVector().getX(), _boundingDePie.getVector3d().getY(), _camara.getVector().getZ()), 2, 1);
		_camara.setVector(_camara.getVector().getX(), -6, _camara.getVector().getZ());
		_bounding = _boundingDePie;
	}
	else
	{
		/*_camara.setVector(_camara.getVector().getX(), _camara.getVector().getY() + _boundingAgachado.getAltura(), _camara.getVector().getZ());
		vector3d posicionAuxiliar(_bounding.getVector3d().getX(), _bounding.getVector3d().getY() + _boundingAgachado.getAltura(), _bounding.getVector3d().getZ());
		_bounding = Cilindro(posicionAuxiliar, _bounding.getAltura(), _bounding.getRadio());*/
		_camara.setVector(_camara.getVector().getX(), -8, _camara.getVector().getZ());
//		_camara.setVector(_camara.getVector().getX(), _camara.getVector().getX() + _boundingAgachado.getAltura(), _camara.getVector().getZ());
		_bounding = _boundingAgachado;
	}
}

void Jugador::ObtenerAngulos()
{
	vector3d objetivo;
	float xrotrad, yrotrad;
	yrotrad = (_camara.getAngulo()->getYrot() / 180 * 3.141592654f);
	xrotrad = (_camara.getAngulo()->getXrot() / 180 * 3.141592654f);

	//Este se usa para el modo normal de disparo
	objetivo.setX(float(sin(yrotrad))*float(cos(xrotrad)));
	objetivo.setY(50.0f*float(sin(-xrotrad)) + _camara.getVector().getY());
	objetivo.setZ(float(cos(yrotrad))*float(cos(xrotrad)));

	_arma.DibujarProyectil(_camara.getVector(), objetivo, xrotrad, yrotrad);
	if(!_arma.getAutomatico())
	{
		if(_arma.getDisparado())
			_arma.Disparo();
		_arma.DibujarProyectil(_camara.getVector(), objetivo, xrotrad, yrotrad);
		_arma.setDisparado(false); //Para hacerlo manual
	}
}

}
