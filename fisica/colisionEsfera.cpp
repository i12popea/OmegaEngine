#include "colisionEsfera.hpp"

using namespace std;
using namespace ed;

namespace ed{

Esfera::Esfera(vector3d vector, float radio)
{
	//setVector3d(vector);
	_coordenadas.setX(vector.getX());
	_coordenadas.setY(vector.getY());
	_coordenadas.setZ(vector.getZ());
	setRadio(radio);
}

Esfera& Esfera::operator = (const Esfera &esfera)
{
	if(this != &esfera)
	{
		_coordenadas = esfera._coordenadas;
		setRadio(esfera.getRadio());
	}
	return *this;
}

}
