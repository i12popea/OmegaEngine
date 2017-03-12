#ifndef _CAMARA_HPP_
#define _CAMARA_HPP_

#ifdef WINDOWS
#include <windows.h> /*Para compilar en Windows*/
#endif

#include <GL/glut.h>
#include <cmath>
#include "vector3d.hpp"
#include "angulo.hpp"

namespace ed{

class Camara
{
private:
	vector3d _posicion;
	Angulo _angulo;
public:
	Camara()
	{
		setVector(0, 0, 0);
		setAngulo(0, 0);
	}
	Camara(float x, float y, float z)
	{
		setVector(x, y, z);
		setAngulo(0, 0);
	}
	Camara(float x, float y, float z, float anguloX, float anguloY)
	{
		setVector(x, y, z);
		setAngulo(anguloX, anguloY);
	}
	
	inline vector3d getVector() const
	{
		return _posicion;
	}
	inline Angulo* getAngulo()
	{
		return &_angulo;
	}

	inline void setVector(float x, float y, float z)
	{
		_posicion.setX(x);
		_posicion.setY(y);
		_posicion.setZ(z);
	}
	inline void setAngulo(float x, float y)
	{
		_angulo.setXrot(x);
		_angulo.setYrot(y);
	}


	Camara & operator = (Camara const &camara);
	
void camara();
void avanzar(bool banderaY);
void retroceder(bool banderaY);
void irIzquierda();
void irDerecha();

};

}

#endif
