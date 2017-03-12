#include "octree.hpp"

using namespace std;
using namespace ed;

namespace ed{

void Octree::determinarCentro(vector<vector3d> vertices)
{
	vector<float> centro;
	vector3d centroHallado;
	vector<vector3d> auxiliar = vertices;
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarX);
	centro.push_back(auxiliar[0].getX()); //Obtengo el mayor valor del eje X
	centro.push_back(auxiliar[auxiliar.size() - 1].getX()); //Obtengo el menor valor del eje X
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarY);
	centro.push_back(auxiliar[0].getY()); //Obtengo el mayor valor del eje Y
	centro.push_back(auxiliar[auxiliar.size() - 1].getY()); //Obtengo el menor valor del eje Y
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarZ);
	centro.push_back(auxiliar[0].getZ()); //Obtengo el mayor valor del eje Z
	centro.push_back(auxiliar[auxiliar.size() - 1].getZ()); //Obtengo el menor valor del eje Z

	//Realizo la distancia media entre los máximos y mínimos para encontrar el centro
	centroHallado.setX((centro[0] - centro[1])/2);
	centroHallado.setY((centro[2] - centro[3])/2);
	centroHallado.setZ((centro[4] - centro[5])/2);

	_centro = centroHallado;
}

void Octree::determinarDimensiones(vector<vector3d> vertices)
{
	vector<float> dimension, dimensionEncontrada;
	vector<vector3d> auxiliar = vertices;
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarX);
	dimension.push_back(auxiliar[0].getX());
	dimension.push_back(auxiliar[auxiliar.size() - 1].getX());
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarY);
	dimension.push_back(auxiliar[0].getY());
	dimension.push_back(auxiliar[auxiliar.size() - 1].getY());
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarZ);
	dimension.push_back(auxiliar[0].getZ());
	dimension.push_back(auxiliar[auxiliar.size() - 1].getZ());

	dimensionEncontrada.push_back(_centro.getX() + dimension[0]);
	dimensionEncontrada.push_back(_centro.getX() + dimension[1]);
	dimensionEncontrada.push_back(_centro.getY() + dimension[2]);
	dimensionEncontrada.push_back(_centro.getY() + dimension[3]);
	dimensionEncontrada.push_back(_centro.getZ() + dimension[4]);
	dimensionEncontrada.push_back(_centro.getZ() + dimension[5]);

	std::sort(dimensionEncontrada.begin(), dimensionEncontrada.end()); //Ordenará de menor a mayor las posibles dimensiones para el octree inicial

	_tamano = dimensionEncontrada[dimensionEncontrada.size() - 1];
}

vector3d determinarCentro(vector<vector3d> vertices)
{
	//vector<float> centro;
	//vector<int> centro;
	vector3d centroHallado;
	/*vector<vector3d> auxiliar = vertices;
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarX);
	centro.push_back((int)auxiliar[0].getX()); //Obtengo el menor valor del eje X
	centro.push_back((int)auxiliar[auxiliar.size() - 1].getX()); //Obtengo el mayor valor del eje X
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarY);
	centro.push_back((int)auxiliar[0].getY()); //Obtengo el menor valor del eje Y
	centro.push_back((int)auxiliar[auxiliar.size() - 1].getY()); //Obtengo el mayor valor del eje Y
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarZ);
	centro.push_back((int)auxiliar[0].getZ()); //Obtengo el menor valor del eje Z
	centro.push_back((int)auxiliar[auxiliar.size() - 1].getZ()); //Obtengo el mayor valor del eje Z

	//Realizo la distancia media entre los máximos y mínimos para encontrar el centro
	centroHallado.setX((centro[1] - centro[0])/2);
	centroHallado.setY((centro[3] - centro[2])/2);
	centroHallado.setZ((centro[5] - centro[4])/2);*/
	for(unsigned int i = 0; i < vertices.size(); i++)
	{
		centroHallado = centroHallado + vertices[i];
	}
	centroHallado = centroHallado / vertices.size();
	//centroHallado = vector3d(roundf( centroHallado.getX() * 10.00 + 0.5 ) / 10.00, roundf( centroHallado.getY() * 10.00 + 0.5 ) / 10.00, roundf( centroHallado.getZ() * 10.00 + 0.5 ) / 10.00);

	return centroHallado;
}

vector3d determinarDimensiones(vector3d centro, vector<vector3d> vertices/*, bool cuboCompleto*/)
{
	vector<float> dimensionX, dimensionY, dimensionZ, dimensionEncontradaX, dimensionEncontradaY, dimensionEncontradaZ;
	//vector<int> dimension, dimensionEncontrada;
	//vector<vector3d> auxiliar, absolutos = vertices;
	vector<vector3d> auxiliar = vertices;
	//for(unsigned int i = 0; i < absolutos.size(); i++)
	//{
	//	auxiliar.push_back(vector3d(abs(absolutos[i].getX()), abs(absolutos[i].getY()), abs(absolutos[i].getZ()))); 
	//}

	std::sort(auxiliar.begin(), auxiliar.end(), ordenarX);
	dimensionX.push_back(auxiliar[0].getX());
	dimensionX.push_back(auxiliar[auxiliar.size() - 1].getX());
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarY);
	dimensionY.push_back(auxiliar[0].getY());
	dimensionY.push_back(auxiliar[auxiliar.size() - 1].getY());
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarZ);
	dimensionZ.push_back(auxiliar[0].getZ());
	dimensionZ.push_back(auxiliar[auxiliar.size() - 1].getZ());

	dimensionEncontradaX.push_back(dimensionX[0] - centro.getX());
	dimensionEncontradaX.push_back(dimensionX[1] - centro.getX());
	dimensionEncontradaY.push_back(dimensionY[0] - centro.getY());
	dimensionEncontradaY.push_back(dimensionY[1] - centro.getY());
	dimensionEncontradaZ.push_back(dimensionZ[0] - centro.getZ());
	dimensionEncontradaZ.push_back(dimensionZ[1] - centro.getZ());

	std::sort(dimensionEncontradaX.begin(), dimensionEncontradaX.end()); //Ordenará de menor a mayor las posibles dimensiones para el octree
	std::sort(dimensionEncontradaY.begin(), dimensionEncontradaY.end()); //Ordenará de menor a mayor las posibles dimensiones para el octree
	std::sort(dimensionEncontradaZ.begin(), dimensionEncontradaZ.end()); //Ordenará de menor a mayor las posibles dimensiones para el octree

	/*float tamanoX = ceil(dimensionEncontradaX[dimensionEncontradaX.size() - 1]);	//Con la función ceil redondeamos a la alza
	float tamanoY = ceil(dimensionEncontradaY[dimensionEncontradaY.size() - 1]);	//Con la función ceil redondeamos a la alza
	float tamanoZ = ceil(dimensionEncontradaZ[dimensionEncontradaZ.size() - 1]);	//Con la función ceil redondeamos a la alza*/
	float tamanoX = roundf( dimensionEncontradaX[dimensionEncontradaX.size() - 1]);// * 10.00 + 0.5 ) / 10.00;
	float tamanoY = roundf( dimensionEncontradaY[dimensionEncontradaY.size() - 1]);// * 10.00 + 0.5 ) / 10.00;
	float tamanoZ = roundf( dimensionEncontradaZ[dimensionEncontradaZ.size() - 1]);// * 10.00 + 0.5 ) / 10.00;
	return vector3d(tamanoX, tamanoY, tamanoZ);
}

void ObtenerCentroDimensiones(vector<vector3d> vertices, vector3d &centro, vector3d& dimensiones)
{
	vector<float> valor;
	vector3d centroHallado;
	vector3d dimensionHallada;
	vector<vector3d> auxiliar = vertices;
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarX);
	valor.push_back(auxiliar[0].getX()); //Obtengo el mayor valor del eje X
	valor.push_back(auxiliar[auxiliar.size() - 1].getX()); //Obtengo el menor valor del eje X
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarY);
	valor.push_back(auxiliar[0].getY()); //Obtengo el mayor valor del eje Y
	valor.push_back(auxiliar[auxiliar.size() - 1].getY()); //Obtengo el menor valor del eje Y
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarZ);
	valor.push_back(auxiliar[0].getZ()); //Obtengo el mayor valor del eje Z
	valor.push_back(auxiliar[auxiliar.size() - 1].getZ()); //Obtengo el menor valor del eje Z

	//Realizo la distancia media entre los máximos y mínimos para encontrar el centro
	centroHallado.setX((valor[0] + valor[1])/2);
	centroHallado.setY((valor[2] + valor[3])/2);
	centroHallado.setZ((valor[4] + valor[5])/2);
	centro = centroHallado;

	dimensionHallada.setX((valor[1] - valor[0])/2);
	dimensionHallada.setY((valor[3] - valor[2])/2);
	dimensionHallada.setZ((valor[5] - valor[4])/2);
	dimensiones = dimensionHallada;
}

void Octree::crearOctree(vector<vector3d> puntos)
{
	vector<vector3d> insertadas;
	NodoOctree *auxiliar = new NodoOctree[puntos.size()];
	for(unsigned int i = 0; i < puntos.size(); i++)
	{
		bool encontrada = false;
		for(unsigned int j = 0; j < insertadas.size(); j++)
		{
			if(insertadas[j] == puntos[i])
			{
				encontrada = true;
				break;
			}
		}
		if(encontrada != true)
		{
			auxiliar[i].setVectorNodo(puntos[i]);
			insertar(auxiliar + i);
			insertadas.push_back(puntos[i]);
		}

	}
}

void Octree::insertar(NodoOctree *puntos)
{
	if(esHoja())
	{
		if(_puntos == NULL)
		{
			_puntos = puntos;
			return;
		}
		else
		{
			NodoOctree *aux = _puntos;
			_puntos = NULL;

			for(int i = 0; i < 8; i++)
			{
				vector3d nuevo = _centro;
				nuevo.setX(nuevo.getX() + _tamano.getX() * (i&4 ? .5f : -.5f));
				nuevo.setY(nuevo.getY() + _tamano.getY() * (i&2 ? .5f : -.5f));
				nuevo.setZ(nuevo.getZ() + _tamano.getZ() * (i&1 ? .5f : -.5f));
				_hijos[i] = new Octree(nuevo, _tamano*.5f);
			}

//cout << "Aux = X: " << aux->getVectorNodo().getX() << ", Y: " << aux->getVectorNodo().getY() << ", Z: " << aux->getVectorNodo().getZ() << endl;
			_hijos[getCuadrante(aux->getVectorNodo())]->insertar(aux);
//cout << "Aux para puntos = X: " << puntos->getVectorNodo().getX() << ", Y: " << puntos->getVectorNodo().getY() << ", Z: " << puntos->getVectorNodo().getZ() << endl;
			_hijos[getCuadrante(puntos->getVectorNodo())]->insertar(puntos);
		}
	}
	else
	{
		int cuadrante = getCuadrante(puntos->getVectorNodo());
//cout << "No es hoja = X: " << puntos->getVectorNodo().getX() << ", Y: " << puntos->getVectorNodo().getY() << ", Z: " << puntos->getVectorNodo().getZ() << endl;
		_hijos[cuadrante]->insertar(puntos);
	}
}

int Octree::getCuadrante(vector3d vector)
{
	int oct = 0;
	if(vector.getX() >= _centro.getX()) oct |= 4;
	if(vector.getY() >= _centro.getY()) oct |= 2;
	if(vector.getZ() >= _centro.getZ()) oct |= 1;
	return oct;
}

void Octree::dibujarOctetos()
{
	if(esHoja())
	{
		if(_puntos != NULL)
		{
			vector<float> vectorDimensiones = {_tamano.getX(), _tamano.getY(), _tamano.getZ()};
			std::sort(vectorDimensiones.begin(), vectorDimensiones.end(), std::greater<float>());
			glPushMatrix();
			glTranslatef(_centro.getX(), _centro.getY(), _centro.getZ());
			glScalef(_tamano.getX()/vectorDimensiones[0], _tamano.getY()/vectorDimensiones[0], _tamano.getZ()/vectorDimensiones[0]);
			glutWireCube(vectorDimensiones[0]*2);
			glPopMatrix();
		}
		else
		{
			vector<float> vectorDimensiones = {_tamano.getX(), _tamano.getY(), _tamano.getZ()};
			std::sort(vectorDimensiones.begin(), vectorDimensiones.end(), std::greater<float>());
			glPushMatrix();
			glTranslatef(_centro.getX(), _centro.getY(), _centro.getZ());
			glScalef(_tamano.getX()/vectorDimensiones[0], _tamano.getY()/vectorDimensiones[0], _tamano.getZ()/vectorDimensiones[0]);
			glutWireCube(vectorDimensiones[0]*2);
			glPopMatrix();
		}
	}
	else
	{
		for(int i = 0; i < 8; i++)
		{
			vector<float> vectorDimensiones = {_hijos[i]->_tamano.getX(), _hijos[i]->_tamano.getY(), _hijos[i]->_tamano.getZ()};
			std::sort(vectorDimensiones.begin(), vectorDimensiones.end(), std::greater<float>());
			glPushMatrix();
			glTranslatef(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			glScalef(_hijos[i]->_tamano.getX()/vectorDimensiones[0], _hijos[i]->_tamano.getY()/vectorDimensiones[0], _hijos[i]->_tamano.getZ()/vectorDimensiones[0]);
			glutWireCube(vectorDimensiones[0]*2);
			glPopMatrix();
			_hijos[i]->dibujarOctetos();
		}
	}
}

bool Octree::interseccionOctree(vector3d vector)
{
	if(esHoja())
	{
		if(_puntos != NULL)
		{
/*if(_puntos == NULL)
	cout << "No hay nada\n";
else
	cout << "Puntos != NULL X: " << _puntos->getX() << ", Y: " << _puntos->getY() << ", Z: " << _puntos->getZ() << endl;*/
			vector3d aux(_centro.getX(), _centro.getY(), _centro.getZ());
			float distX = distanciaX(aux, vector);
			float distY = distanciaY(aux, vector);
			float distZ = distanciaZ(aux, vector);
//cout << "Puntos != NULL X: " << _centro.getX() << ", Y: " << _centro.getY() << ", Z: " << _centro.getZ() << ", tamano: " << _tamano << endl;
			if((distX <= _tamano.getX()) && (distY <= _tamano.getY()) && (distZ <= _tamano.getZ()))
				return true;
			return false;
		}
	}
	else
	{
		for(int i = 0; i < 8; i++)
		{
			vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			float distX = distanciaX(aux, vector);
			float distY = distanciaY(aux, vector);
			float distZ = distanciaZ(aux, vector);
			if((distX > _hijos[i]->_tamano.getX()) || (distY > _hijos[i]->_tamano.getY()) || (distZ > _hijos[i]->_tamano.getZ()))
				continue;

			return _hijos[i]->interseccionOctree(vector);
		}
	}
	return false;
}

bool Octree::interseccionOctreeCilindro(Cilindro cilindro, Box &octetoAuxiliar, bool &suelo, bool &techo, bool &pared, float &diferenciaX, float &diferenciaZ)
{
	if(esHoja())
	{
		if(_puntos != NULL)
		{
			vector3d aux(_centro.getX(), _centro.getY(), _centro.getZ());
			Box octeto(aux, _tamano.getY(), _tamano.getZ(), _tamano.getX());
			octetoAuxiliar = octeto;
			if(ColisionCilindroOcteto(octeto, cilindro, suelo, techo, pared, diferenciaX, diferenciaZ))
			//	return false;
				return true;
			return false;
			/*float distX = distanciaX(aux, vector);
			float distY = distanciaY(aux, vector);
			float distZ = distanciaZ(aux, vector);
			if((distX <= _tamano.getX()) && (distY <= _tamano.getY()) && (distZ <= _tamano.getZ()))
				return true;
			return false;*/
		}
	}
	else
	{
		for(int i = 0; i < 8; i++)
		{
			/*vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			float distX = distanciaX(aux, vector);
			float distY = distanciaY(aux, vector);
			float distZ = distanciaZ(aux, vector);
			if((distX > _hijos[i]->_tamano.getX()) || (distY > _hijos[i]->_tamano.getY()) || (distZ > _hijos[i]->_tamano.getZ()))
				continue;*/
			vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			Box octeto(aux, _hijos[i]->_tamano.getY(), _hijos[i]->_tamano.getZ(), _hijos[i]->_tamano.getX());
			if(!ColisionCilindroOcteto(octeto, cilindro, suelo, techo, pared, diferenciaX, diferenciaZ))
				continue;

			return _hijos[i]->interseccionOctreeCilindro(cilindro, octetoAuxiliar, suelo, techo, pared, diferenciaX, diferenciaZ);
		}
	}
	return false;
	//return true;
}

void Octree::interseccionOctreeCilindro(Cilindro cilindro, Box &octetoAuxiliar, bool &suelo, bool &techo, bool &pared, float &diferenciaX, float &diferenciaZ, bool &resultado)
{
	if(esHoja())
	{
		if(_puntos != NULL)
		{
			vector3d aux(_centro.getX(), _centro.getY(), _centro.getZ());
			Box octeto(aux, _tamano.getY(), _tamano.getZ(), _tamano.getX());
			octetoAuxiliar = octeto;
			if(!ColisionCilindroOcteto(octeto, cilindro, suelo, techo, pared, diferenciaX, diferenciaZ))
				return;
			resultado = true;
		}
	}
	else
	{
		for(int i = 0; i < 8; i++)
		{
			vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			Box octeto(aux, _hijos[i]->_tamano.getY(), _hijos[i]->_tamano.getZ(), _hijos[i]->_tamano.getX());
			if(!ColisionCilindroOcteto(octeto, cilindro, suelo, techo, pared, diferenciaX, diferenciaZ))
				continue;

			return _hijos[i]->interseccionOctreeCilindro(cilindro, octetoAuxiliar, suelo, techo, pared, diferenciaX, diferenciaZ, resultado);
		}
	}
}

bool Octree::interseccionOctreeBox(Box objeto, Box &octetoAuxiliar)
{
	if(esHoja())
	{
		if(_puntos != NULL)
		{
			vector3d aux(_centro.getX(), _centro.getY(), _centro.getZ());
			Box octeto(aux, _tamano.getY(), _tamano.getZ(), _tamano.getX());
			octetoAuxiliar = octeto;
			if(!interseccion(objeto, octeto))
			//	return false;
				return true;
			return false;
			/*float distX = distanciaX(aux, vector);
			float distY = distanciaY(aux, vector);
			float distZ = distanciaZ(aux, vector);

			if((distX <= _tamano.getX()) && (distY <= _tamano.getY()) && (distZ <= _tamano.getZ()))
				return true;
			return false;*/
		}
	}
	else
	{
		for(int i = 0; i < 8; i++)
		{
			/*vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			float distX = distanciaX(aux, vector);
			float distY = distanciaY(aux, vector);
			float distZ = distanciaZ(aux, vector);
			if((distX > _hijos[i]->_tamano.getX()) || (distY > _hijos[i]->_tamano.getY()) || (distZ > _hijos[i]->_tamano.getZ()))*/
			vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			Box octeto(aux, _hijos[i]->_tamano.getY(), _hijos[i]->_tamano.getZ(), _hijos[i]->_tamano.getX());
			//octetoAuxiliar = octeto;
			if(!interseccion(objeto, octeto))
				continue;

			return _hijos[i]->interseccionOctreeBox(objeto, octetoAuxiliar);
		}
	}
	return false;
	//return true;
}

bool Octree::FrustumOctreeOctetos(Frustum frustum)
{
	bool resultado = false;
	if(esHoja())
	{
		if(_puntos != NULL)
		{
			vector3d aux(_centro.getX(), _centro.getY(), _centro.getZ());
			//Box octeto(aux, _tamano.getY(), _tamano.getZ(), _tamano.getX());
			if(frustum.CubeInFrustum2(aux, _tamano.getY(), _tamano.getZ(), _tamano.getX()) != 0)
			resultado = true;
			/*	return true;
			return false;*/
		}
	}
	else
	{
		for(int i = 0; i < 8; i++)
		{
			vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			//Box octeto(aux, _hijos[i]->_tamano.getY(), _hijos[i]->_tamano.getZ(), _hijos[i]->_tamano.getX());
			if(0 == frustum.CubeInFrustum2(aux, _hijos[i]->_tamano.getY(), _hijos[i]->_tamano.getZ(), _hijos[i]->_tamano.getX()))
				continue;

			return _hijos[i]->FrustumOctreeOctetos(frustum);
		}
	}
	//return false;
	return resultado;
}

void Octree::FrustumOctreeOctetos(Frustum frustum, bool &resultado)
{
	if(esHoja())
	{
		if(_puntos != NULL)
		{
			vector3d aux(_centro.getX(), _centro.getY(), _centro.getZ());
			if(frustum.CubeInFrustum2(aux, _tamano.getY(), _tamano.getZ(), _tamano.getX()) == 0)
				return;
			resultado = true;
		}
	}
	else
	{
		for(int i = 0; i < 8; i++)
		{
			vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			//Box octeto(aux, _hijos[i]->_tamano.getY(), _hijos[i]->_tamano.getZ(), _hijos[i]->_tamano.getX());
			if(0 == frustum.CubeInFrustum2(aux, _hijos[i]->_tamano.getY(), _hijos[i]->_tamano.getZ(), _hijos[i]->_tamano.getX()))
				continue;

			return _hijos[i]->FrustumOctreeOctetos(frustum, resultado);
		}
	}
}

/*bool Octree::FrustumOctreePuntos(Frustum frustum)
{
	if(esHoja())
	{
		if(_puntos != NULL)
		{
			//vector3d aux(_centro.getX(), _centro.getY(), _centro.getZ());
			//if(frustum.CubeInFrustum(aux, _tamano.getY(), _tamano.getZ(), _tamano.getX()))
			const vector3d& punto = _puntos->getVectorNodo();
			//if(frustum.PointInFrustum(_puntos->getVectorNodo()))
			if(frustum.PointInFrustum(punto))
				return true;
			return false;
		}
	}
	else
	{
		for(int i = 0; i < 8; i++)
		{
			//vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			//if(!frustum.CubeInFrustum(aux, _hijos[i]->_tamano.getY(), _hijos[i]->_tamano.getZ(), _hijos[i]->_tamano.getX()))
//			const vector3d& punto = _hijos[i]->_puntos->getVectorNodo();
			//if(!frustum.PointInFrustum(_hijos[i]->_puntos->getVectorNodo()))
//			if(!frustum.PointInFrustum(punto))
//				continue;
			vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			if(!frustum.CubeInFrustum(aux, _hijos[i]->_tamano.getY(), _hijos[i]->_tamano.getZ(), _hijos[i]->_tamano.getX()))
				continue;

			return _hijos[i]->FrustumOctreePuntos(frustum);
		}
	}
	return false;
}*/
bool Octree::FrustumOctreePuntos(Frustum frustum)
{
	if(esHoja())
	{
		if(_puntos != NULL)
		{
			//vector3d aux(_centro.getX(), _centro.getY(), _centro.getZ());
			//if(frustum.CubeInFrustum(aux, _tamano.getY(), _tamano.getZ(), _tamano.getX()))
			vector3d punto = _puntos->getVectorNodo();
			//if(frustum.PointInFrustum(_puntos->getVectorNodo()))
			if(frustum.PointInFrustum(punto))
				return true;
			return false;
		}
	}
	else
	{
		for(int i = 0; i < 8; i++)
		{
			//vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			//if(!frustum.CubeInFrustum(aux, _hijos[i]->_tamano.getY(), _hijos[i]->_tamano.getZ(), _hijos[i]->_tamano.getX()))
//			const vector3d& punto = _hijos[i]->_puntos->getVectorNodo();
			//if(!frustum.PointInFrustum(_hijos[i]->_puntos->getVectorNodo()))
//			if(!frustum.PointInFrustum(punto))
//				continue;
			vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			if(0 == frustum.CubeInFrustum2(aux, _hijos[i]->_tamano.getY(), _hijos[i]->_tamano.getZ(), _hijos[i]->_tamano.getX()))
				continue;

			return _hijos[i]->FrustumOctreePuntos(frustum);
		}
	}
	return false;
}

void Octree::FrustumOctreePuntos(Frustum frustum, bool &resultado)
{
	if(esHoja())
	{
		if(_puntos != NULL)
		{
			vector3d punto = _puntos->getVectorNodo();
			if(frustum.PointInFrustum(punto))
				return;
		}
	}
	else
	{
		for(int i = 0; i < 8; i++)
		{
			vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
			if(0 == frustum.CubeInFrustum2(aux, _hijos[i]->_tamano.getY(), _hijos[i]->_tamano.getZ(), _hijos[i]->_tamano.getX()))
				continue;

			return _hijos[i]->FrustumOctreePuntos(frustum, resultado);
		}
	}
}

//Ya modificaré este
/*void Octree::interseccionOctree(vector3d vector, bool &resultado)
{
	if(esHoja())
	{
//cout << "Es hoja\n";
		if(_puntos != NULL)
		{
			vector3d aux(_centro.getX(), _centro.getY(), _centro.getZ());
			float distX = distanciaX(aux, vector);
			float distY = distanciaY(aux, vector);
			float distZ = distanciaZ(aux, vector);

			if((distX <= _tamano) && (distY <= _tamano) && (distZ <= _tamano))
			{
				resultado = true;
				//return;
			}
			else
			{
				resultado = false;
				//return;
			}
//			cout << "Resultado de puntos != NULL: " << resultado << endl;
		}
	}
	else
	{
//cout << "No es hoja\n";
			for(int i = 0; i < 8; i++)
			{

				vector3d aux(_hijos[i]->_centro.getX(), _hijos[i]->_centro.getY(), _hijos[i]->_centro.getZ());
				float distX = distanciaX(aux, vector);
				float distY = distanciaY(aux, vector);
				float distZ = distanciaZ(aux, vector);
				if((distX <= _hijos[i]->_tamano) && (distY <= _hijos[i]->_tamano) && (distZ <= _hijos[i]->_tamano) && (_hijos[i]->_puntos != NULL))
				{
					resultado = true;
					return;
				}
				else
				{
					resultado = false;
					return;
				}
				_hijos[i]->interseccionOctree(vector, resultado);
			}
		//}
	}
}*/

bool vectorMenor(const vector3d &vector1, const vector3d &vector2)
{
	return (vector1.getX() < vector2.getX()) || (vector1.getY() < vector2.getY()) || (vector1.getZ() < vector2.getZ());
}

bool compararVector(const vector3d &vector1, const vector3d &vector2)
{
	return (vector1.getX() == vector2.getX()) && (vector1.getY() == vector2.getY()) && (vector1.getZ() == vector2.getZ());
}


bool ordenarX(const vector3d &vector1, const vector3d &vector2)
{
	return (vector1.getX() < vector2.getX());
}

bool ordenarY(const vector3d &vector1, const vector3d &vector2)
{
	return (vector1.getY() < vector2.getY());
}

bool ordenarZ(const vector3d &vector1, const vector3d &vector2)
{
	return (vector1.getZ() < vector2.getZ());
}

}
