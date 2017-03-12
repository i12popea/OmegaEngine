#ifndef _COLISIONCILINDRO_HPP_
#define _COLISIONCILINDRO_HPP_

#include <iostream>
#include <cmath>
#include "../vector3d.hpp"

namespace ed{

class Cilindro{
	private:
		vector3d _centro;
		float _altura;	//La mitad de la altura total del cilindro
		float _radio;
	public:
		Cilindro(vector3d centro = vector3d(0, 0, 0), float altura = 0, float radio = 0);

		inline float getRadio() const
		{
			return _radio;
		}
		inline void setRadio(float radio)
		{
			_radio = radio;
		}
		inline float getAltura() const
		{
			return _altura;
		}
		inline void setAltura(float altura)
		{
			_altura = altura;
		}
		inline vector3d getVector3d()
		{
			return _centro;
		}
		inline void setVector3d(vector3d vector)
		{
			//_coordenadas=vector;
			_centro.setX(vector.getX());
			_centro.setY(vector.getY());
			_centro.setZ(vector.getZ());
		}

		Cilindro& operator = (const Cilindro &cilindro);

};

/*float distanciaX(Esfera uno, Esfera dos);
float distanciaY(Esfera uno, Esfera dos);
float distanciaZ(Esfera uno, Esfera dos);
float distancia(Esfera uno, Esfera dos);
bool interseccion(Esfera esferaUno, Esfera esferaDos);*/

}

#endif
