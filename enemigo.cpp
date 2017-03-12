#include "enemigo.hpp"

using namespace std;
using namespace ed;

namespace ed
{

/*void Jugador::MostrarArma()
{
	_arma.DibujarArma();
}*/

void Enemigo::SaludDanada(int cantidad)
{
	_salud = _salud - cantidad;
}

void Enemigo::Caminar()
{
	Avanzar();
	if(!_colision && _nearcollision)
		_brain.setEstado(CAMBIARDIR);
	if(_activo)
	{
		
	}
	if(_muerto)
		_brain.setEstado(MUERTO);
}

void Enemigo::Muerto()
{
	cout << "Enemigo muerto\n";
}

void Enemigo::Perseguir()
{
	if(_activo)
	{
		if(distanciaEntrePuntos2D(_posicion, _PosicionJugador) <= 0.5) //Si está en contacto
			_brain.setEstado(ATACAR);
	}
	if(_muerto)
		_brain.setEstado(MUERTO);
}

void Enemigo::CambiarDir()
{
	_angulo.setYrot(_angulo.getYrot() + 1);
	if(_angulo.getYrot() < 0.0)
		_angulo.setYrot(_angulo.getYrot() + 360.0);
	else
		if(_angulo.getYrot() >= 360.0)
			_angulo.setYrot(_angulo.getYrot() - 360.0);

	if(_activo)
	{
		
	}
	if(_muerto)
		_brain.setEstado(MUERTO);
}

void Enemigo::Activo()
{
	_activo = true;
	if(distanciaEntrePuntos2D(_posicion, _PosicionJugador) > 0.5) //Si no está en contacto
		_brain.setEstado(PERSEGUIR);
	if(distanciaEntrePuntos2D(_posicion, _PosicionJugador) <= 0.5) //Si está en contacto
		_brain.setEstado(ATACAR);
	if(_muerto)
		_brain.setEstado(MUERTO);
}

void Enemigo::Esquivar()
{
	if(_activo)
	{
		
	}
	if(_muerto)
		_brain.setEstado(MUERTO);
}

void Enemigo::Atacar()
{
	if(_activo)
	{
		if(distanciaEntrePuntos2D(_posicion, _PosicionJugador) > 0.5) //Si no está en contacto
			_brain.setEstado(PERSEGUIR);
	}
	if(_muerto)
		_brain.setEstado(MUERTO);
}

void Enemigo::Avanzar()
{
	float yrotrad;
	yrotrad = (_angulo.getYrot() / 180 * 3.141592654f);
	_posicion.setX(_posicion.getX() + float(sin(yrotrad))*0.25f);
	_posicion.setZ(_posicion.getZ() - float(cos(yrotrad))*0.25f);

	_bounding.setVector3d(_posicion);
}

void Enemigo::ColisionEnemigo(vector<Box> boxes, vector<Esfera> esferas, vector<Octree*> objetoOctree)
{
	_caer = false;
	_colision = false;
	_nearcollision = false;

	Cilindro nuevoBounding = _bounding;
	vector3d nuevaposicion = _bounding.getVector3d();
	float yrotrad = (_angulo.getYrot() / 180 * 3.141592654f);
	nuevaposicion.setX(nuevaposicion.getX() + float(sin(yrotrad))*10.0); nuevaposicion.setZ(nuevaposicion.getZ() - float(cos(yrotrad))*10.0);
	nuevoBounding.setVector3d(nuevaposicion);

	bool suelo = false, techo = false, pared = false;
	float diferenciaX, diferenciaZ;

	for(unsigned int i = 0; i < boxes.size(); i++)
	{
		if(ColisionCilindroOcteto(boxes[i], nuevoBounding, suelo, techo, pared, diferenciaX, diferenciaZ))
		{
			if(pared)
				_nearcollision = true;
		}
		if(ColisionCilindroOcteto(boxes[i], _bounding, suelo, techo, pared, diferenciaX, diferenciaZ))
		{
			if(!suelo)
				_caer = true;
			if(pared)
				_colision = true;
		}
	}
	for(unsigned int i = 0; i < esferas.size(); i++)
	{
		if(ColisionCilindroEsfera(esferas[i], nuevoBounding, suelo, techo, pared, diferenciaX, diferenciaZ))
		{
			if(pared)
				_nearcollision = true;
		}
		if(ColisionCilindroEsfera(esferas[i], _bounding, suelo, techo, pared, diferenciaX, diferenciaZ))
		{
			if(!suelo)
				_caer = true;
			if(pared)
				_colision = true;
		}
	}
	for(unsigned int i = 0; i < objetoOctree.size(); i++)
	{
		Box octetoAuxiliar;
		if(objetoOctree[i]->interseccionOctreeCilindro(nuevoBounding, octetoAuxiliar, suelo, techo, pared, diferenciaX, diferenciaZ))
		{
			if(pared)
				_nearcollision = true;
		}
		if(objetoOctree[i]->interseccionOctreeCilindro(_bounding, octetoAuxiliar, suelo, techo, pared, diferenciaX, diferenciaZ))
		{
			if(!suelo)
				_caer = true;
			if(pared)
				_colision = true;
		}
	}
}

void Enemigo::ActualizarEstado()
{
	if(_brain.getEstado() == CAMINAR)
		Caminar();
	if(_brain.getEstado() == MUERTO)
		Muerto();
	if(_brain.getEstado() == PERSEGUIR)
		Perseguir();
	if(_brain.getEstado() == CAMBIARDIR)
		CambiarDir();
	if(_brain.getEstado() == ACTIVO)
		Activo();
	if(_brain.getEstado() == ESQUIVAR)
		Esquivar();
	if(_brain.getEstado() == ATACAR)
		Atacar();
}

/*void Jugador::SaludRegenerada()
{
	//Iniciamos una semilla aleatoria
	srand(time(NULL));
	//Escogemos una cantidad entre 10 y 20
	int cantidad = 10 + ( rand() % ( 20 - 10 + 1 ) );
	if(_salud + cantidad > 100)
		_salud = 100;
	else
		_salud = _salud + cantidad;
}*/

/*void Jugador::ActualizarPosicion()
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
		if(objetoOctree[i]->interseccionOctreeCilindro(_bounding, octetoAuxiliar, suelo, techo, pared, diferenciaX, diferenciaZ))
		{
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
	for(unsigned int i = 0; i < boxes.size(); i++)
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
	}
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
		_camara.setVector(_camara.getVector().getX(), _boundingDePie.getVector3d().getY() + _boundingDePie.getAltura(), _camara.getVector().getZ());
		_bounding = _boundingDePie;
	}
	else
	{
		_camara.setVector(_camara.getVector().getX(), _boundingAgachado.getVector3d().getY() + _boundingAgachado.getAltura(), _camara.getVector().getZ());
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
}*/

}
