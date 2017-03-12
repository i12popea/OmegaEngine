#ifndef _COLISIONESFERA_HPP_
#define _COLISIONESFERA_HPP_

#include <iostream>
#include <cmath>
#include "../vector3d.hpp"

namespace ed{

class Esfera{
	private:
		vector3d _coordenadas;
		float _radio;
	public:
		Esfera(vector3d vector=vector3d(0, 0, 0), float radio=0);
		/*Esfera(vector3d vector=0, float radio=0)
		{
			setVector3d(vector);
			setRadio(radio);
		}*/
		inline float getRadio() const
		{
			return _radio;
		}
		inline void setRadio(float radio)
		{
			_radio=radio;
		}
		inline vector3d getVector3d()
		{
			return _coordenadas;
		}
		inline void setVector3d(vector3d vector)
		{
			//_coordenadas=vector;
			_coordenadas.setX(vector.getX());
			_coordenadas.setY(vector.getY());
			_coordenadas.setZ(vector.getZ());
		}

		Esfera& operator = (const Esfera &esfera);

};

/*float distanciaX(Esfera uno, Esfera dos);
float distanciaY(Esfera uno, Esfera dos);
float distanciaZ(Esfera uno, Esfera dos);
float distancia(Esfera uno, Esfera dos);
bool interseccion(Esfera esferaUno, Esfera esferaDos);*/

}

#endif
