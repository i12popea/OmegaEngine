#include "colisionCilindro.hpp"

using namespace std;
using namespace ed;

namespace ed{

Cilindro::Cilindro(vector3d vector, float altura, float radio)
{
	_centro.setX(vector.getX());
	_centro.setY(vector.getY());
	_centro.setZ(vector.getZ());
	setAltura(altura);
	setRadio(radio);
}

Cilindro& Cilindro::operator = (const Cilindro &cilindro)
{
	if(this != &cilindro)
	{
		_centro = cilindro._centro;
		setAltura(cilindro.getAltura());
		setRadio(cilindro.getRadio());
	}
	return *this;
}

}
