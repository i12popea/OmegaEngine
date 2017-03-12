#ifndef _ILUMINACION_HPP_
#define _ILUMINACION_HPP_

#include <iostream>
#include <vector>
#include "vector3d.hpp"
#include <GL/glut.h>

using namespace std;
using std::vector;

namespace ed{

class Iluminacion
{
private:
	vector3d _posicion;
	GLfloat _color[4];
	vector3d _ambiente;
	vector3d _difusa;
	vector3d _especular;
public:
	inline vector3d getPosicion()
	{
		return _posicion;
	}
	inline GLfloat* getColor()
	{
		return _color;
	}
	inline vector3d getAmbiente()
	{
		return _ambiente;
	}
	inline vector3d getDifusa()
	{
		return _difusa;
	}
	inline vector3d getEspecular()
	{
		return _especular;
	}

	inline void setPosicion(vector3d posicion)
	{
		_posicion = posicion;
	}
	inline void setColor(GLfloat color[4])
	{
		_color[0] = color[0];
		_color[1] = color[1];
		_color[2] = color[2];
		_color[3] = color[3];
	}
	inline void setAmbiente(vector3d ambiente)
	{
		_ambiente = ambiente;
	}
	inline void setDifusa(vector3d difusa)
	{
		_difusa = difusa;
	}
	inline void setEspecular(vector3d especular)
	{
		_especular = especular;
	}
};

class ListaIluminacion
{
private:
	vector<Iluminacion> _focos;
	GLfloat _LightPosition[96]; //32 posiciones del foco
	GLfloat _LightColor[128]; //32 fuentes de color para los 32 focos
public:
	inline Iluminacion getFoco(int indice)
	{
		return _focos[indice];
	}
	inline GLfloat* getLightPosition()
	{
		return _LightPosition;
	}
	inline GLfloat* getLightColor()
	{
		return _LightColor;
	}
	inline int getCantidadFocos()
	{
		return _focos.size();
	}

	void IniciarIluminacion();
	void IluminarEscena();
	void InsertarFoco(Iluminacion foco);
};

}

#endif
