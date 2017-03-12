#ifndef _OCTREE_HPP_
#define _OCTREE_HPP_

#include <iostream>
#include <algorithm>
#include "../vector3d.hpp"
#include "colision.hpp"
#include "../Frustum.hpp"
#include <GL/glut.h>

using std::find;

namespace ed{

class NodoOctree{
private:
	vector3d _puntos;
public:
	NodoOctree() {}
	NodoOctree(const vector3d &puntos)
	{
		_puntos = puntos;
	}

	inline vector3d getVectorNodo() const
	{
		return _puntos;
	}

	inline void setVectorNodo(const vector3d &puntos)
	{
		_puntos = puntos;
	}
};



class Octree{
private:
	vector3d _centro;
	vector3d _tamano;
//	float _tamano;
	Octree *_hijos[8];
	NodoOctree *_puntos;
//	vector3d *_puntos;
public:
	Octree(const vector3d &centro, const vector3d &tamano)
	{
		_centro = centro;
		_tamano = tamano;
		_puntos = NULL;

		for(int i = 0; i < 8; i++)
			_hijos[i] = NULL;
	}
	Octree(const Octree &copia)
	{
		_centro = copia._centro;
		_tamano = copia._tamano;
		_puntos = copia._puntos;
	}
	~Octree()
	{
		for(int i = 0; i < 8; i++)
			delete _hijos[i];
	}

	inline vector3d getCentro() const
	{
		return _centro;
	}

	inline vector3d getTamano() const
	{
		return _tamano;
	}

	bool esHoja()
	{
		//return _hijos[0] == NULL && _hijos[1] == NULL && _hijos[2] == NULL && _hijos[3] == NULL && _hijos[4] == NULL && _hijos[5] == NULL && _hijos[6] == NULL && _hijos[7] == NULL;
		return _hijos[0] == NULL;
/*		if(_hijos[0] == NULL)
		{
cout << "cierto\n";
			return true;
		}
		else
		{
cout << "falso\n";
			return false;
		}*/
	}

	void determinarCentro(vector<vector3d> vertices);
	void determinarDimensiones(vector<vector3d> vertices);
	void crearOctree(vector<vector3d> puntos);
//	void insertar(vector3d *puntos);
	void insertar(NodoOctree *puntos);
	int getCuadrante(vector3d vector);
	void dibujarOctetos();
	bool interseccionOctree(vector3d vector);
	bool interseccionOctreeCilindro(Cilindro cilindro, Box &octetoAuxiliar, bool &suelo, bool &techo, bool &pared, float &diferenciaX, float &diferenciaZ);
	void interseccionOctreeCilindro(Cilindro cilindro, Box &octetoAuxiliar, bool &suelo, bool &techo, bool &pared, float &diferenciaX, float &diferenciaZ, bool &resultado);
	bool interseccionOctreeBox(Box objeto, Box &octetoAuxiliar);
	void interseccionOctree(vector3d vector, bool &resultado);
	bool FrustumOctreeOctetos(Frustum frustum);
	void FrustumOctreeOctetos(Frustum frustum, bool &resultado);
	bool FrustumOctreePuntos(Frustum frustum);
	void FrustumOctreePuntos(Frustum frustum, bool &resultado);
};

//Funciones
vector3d determinarCentro(vector<vector3d> vertices);
vector3d determinarDimensiones(vector3d centro, vector<vector3d> vertices/*, bool cuboCompleto*/);
void ObtenerCentroDimensiones(vector<vector3d> vertices, vector3d &centro, vector3d& dimensiones);

bool vectorMenor(const vector3d &vector1, const vector3d &vector2);
bool compararVector(const vector3d &vector1, const vector3d &vector2);

bool ordenarX(const vector3d &a, const vector3d &b);
bool ordenarY(const vector3d &a, const vector3d &b);
bool ordenarZ(const vector3d &a, const vector3d &b);

}


#endif

/*
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
using std::vector;

struct Points
{
    float x,y,z;
};

bool ordenarX(const Points &vector1, const Points &vector2)
{
	return (vector1.x < vector2.x);
}

bool ordenarY(const Points &vector1, const Points &vector2)
{
	return (vector1.y < vector2.y);
}

bool ordenarZ(const Points &vector1, const Points &vector2)
{
	return (vector1.z < vector2.z);
}

Points determinarCentro(vector<Points> vertices)
{
	vector<int> centro;
	Points centroHallado;
	for(unsigned int i = 0; i < vertices.size(); i++)
	{
		centroHallado.x = centroHallado.x + vertices[i].x;
		centroHallado.y = centroHallado.y + vertices[i].y;
		centroHallado.z = centroHallado.z + vertices[i].z;
	}
	centroHallado.x = centroHallado.x / vertices.size();
	centroHallado.y = centroHallado.y / vertices.size();
	centroHallado.z = centroHallado.z / vertices.size();

	return centroHallado;
}

Points determinarDimensiones(Points centro, vector<Points> vertices)
{
	vector<float> dimensionX, dimensionY, dimensionZ, dimensionEncontradaX, dimensionEncontradaY, dimensionEncontradaZ;
	//vector<int> dimension, dimensionEncontrada;
	vector<Points> auxiliar = vertices;

	std::sort(auxiliar.begin(), auxiliar.end(), ordenarX);
	dimensionX.push_back(auxiliar[0].x);
	dimensionX.push_back(auxiliar[auxiliar.size() - 1].x);
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarY);
	dimensionY.push_back(auxiliar[0].y);
	dimensionY.push_back(auxiliar[auxiliar.size() - 1].y);
	std::sort(auxiliar.begin(), auxiliar.end(), ordenarZ);
	dimensionZ.push_back(auxiliar[0].z);
	dimensionZ.push_back(auxiliar[auxiliar.size() - 1].z);

	dimensionEncontradaX.push_back(dimensionX[0] - centro.x);
	dimensionEncontradaX.push_back(dimensionX[1] - centro.x);
	dimensionEncontradaY.push_back(dimensionY[0] - centro.y);
	dimensionEncontradaY.push_back(dimensionY[1] - centro.y);
	dimensionEncontradaZ.push_back(dimensionZ[0] - centro.z);
	dimensionEncontradaZ.push_back(dimensionZ[1] - centro.z);

	std::sort(dimensionEncontradaX.begin(), dimensionEncontradaX.end()); //Ordenará de menor a mayor las posibles dimensiones para el octree
	std::sort(dimensionEncontradaY.begin(), dimensionEncontradaY.end()); //Ordenará de menor a mayor las posibles dimensiones para el octree
	std::sort(dimensionEncontradaZ.begin(), dimensionEncontradaZ.end()); //Ordenará de menor a mayor las posibles dimensiones para el octree

	float tamanoX = ceil(dimensionEncontradaX[dimensionEncontradaX.size() - 1]);	//Con la función ceil redondeamos a la alza
	float tamanoY = ceil(dimensionEncontradaY[dimensionEncontradaY.size() - 1]);	//Con la función ceil redondeamos a la alza
	float tamanoZ = ceil(dimensionEncontradaZ[dimensionEncontradaZ.size() - 1]);	//Con la función ceil redondeamos a la alza
	
	Points puntos; puntos.x = tamanoX; puntos.y = tamanoY; puntos.z = tamanoZ;
	return puntos;
}

int main()
{
  vector<Points> v
    { {0.0, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 3.0, 0.0},
    {0.0, 3.0, 1.0},
    {1.0, 0.0, 0.0},
    {1.0, 0.0, 1.0},
    {1.0, 3.0, 0.0},
    {1.0, 3.0, 1.0},
    };
    
    Points centro = determinarCentro(v);
    Points dimensiones = determinarDimensiones(centro, v);
    
    cout << "X: " << centro.x << ", Y: " << centro.y << ", Z: " << centro.z << endl;
    cout << "X: " << dimensiones.x << ", Y: " << dimensiones.y << ", Z: " << dimensiones.z << endl;
    
  return 0;
}
*/
