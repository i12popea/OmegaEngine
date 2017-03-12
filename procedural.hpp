#ifndef _PROCEDURAL_HPP_
#define _PROCEDURAL_HPP_

#include "vector3d.hpp"
#include <vector>
#include <time.h>
#include <GL/glut.h>

using namespace std;
using namespace ed;
using std::vector;

//namespace ed
//{

extern vector<vector3d> hierba1;
extern vector<vector3d> hierba2;
extern vector<vector3d> hierba3;
extern vector<vector3d> hierba4;
extern vector<vector3d> hierba5;
extern vector<vector3d> hierba6;
extern vector<vector3d> color1;
extern vector<vector3d> color2;

//extern vector<vector3d> cesped, colorCesped;

vector<vector3d> suma(vector<vector3d> hierba, vector3d posicion);
void InicializarHierba1();
void InicializarHierba2();
void InicializarHierba3();
void InicializarHierba4();
void InicializarHierba5();
void InicializarHierba6();
void InicializarColor1();
void InicializarColor2();
void IniciarHierba();
void CrearCesped(vector3d inicio, vector3d fin, vector<vector3d> &cesped, vector<vector3d> &colorCesped);
void RenderizarCesped(vector<vector3d> cesped, vector<vector3d> colorCesped);

//}

/*
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
using std::vector;

class vector3d
{
public:
	float _x, _y, _z;
	//Constructor parametrizado
	vector3d(float x=0.0, float y=0.0, float z=0.0)
	{
		_x = x;
		_y = y;
		_z = z;
	}
	//Constructor de copia
	vector3d(vector3d const &v)
	{
		_x = v._x;
		_y = v._y;
		_z = v._z;
	}
	
	vector3d operator + (vector3d const &vector)
    {
        vector3d aux;
        aux._x = (_x + vector._x);
        aux._y = (_y + vector._y);
        aux._z = (_z + vector._z);
        return aux;
    }
};

vector<vector3d> hierba1;
vector<vector3d> hierba2;

void InicializarHierba1()
{
	hierba1.push_back(vector3d(0, 0, 0));
	hierba1.push_back(vector3d(0.1, 0, 0));
	hierba1.push_back(vector3d(0, 0.2, 0));

	hierba1.push_back(vector3d(0.1, 0, 0));
	hierba1.push_back(vector3d(0.1, 0.2, 0));
	hierba1.push_back(vector3d(0, 0.2, 0));

	hierba1.push_back(vector3d(0, 0.2, 0));
	hierba1.push_back(vector3d(0.1, 0.2, 0));
	hierba1.push_back(vector3d(0, 0.4, 0));

	hierba1.push_back(vector3d(0.1, 0.2, 0));
	hierba1.push_back(vector3d(0.1, 0.4, 0));
	hierba1.push_back(vector3d(0, 0.4, 0));

	hierba1.push_back(vector3d(0.1, 0.4, 0));
	hierba1.push_back(vector3d(0.1, 0.5, 0));
	hierba1.push_back(vector3d(0, 0.4, 0));
}

void InicializarHierba2()
{
	hierba2.push_back(vector3d(0, 0, 0));
	hierba2.push_back(vector3d(0, 0, 0.1));
	hierba2.push_back(vector3d(0, 0.2, 0));

	hierba2.push_back(vector3d(0, 0, 0.1));
	hierba2.push_back(vector3d(0, 0.2, 0.1));
	hierba2.push_back(vector3d(0, 0.2, 0));

	hierba2.push_back(vector3d(0, 0.2, 0));
	hierba2.push_back(vector3d(0, 0.2, 0.1));
	hierba2.push_back(vector3d(0, 0.4, 0));

	hierba2.push_back(vector3d(0, 0.2, 0.1));
	hierba2.push_back(vector3d(0, 0.4, 0.1));
	hierba2.push_back(vector3d(0, 0.4, 0));

	hierba2.push_back(vector3d(0, 0.4, 0.1));
	hierba2.push_back(vector3d(0, 0.5, 0.1));
	hierba2.push_back(vector3d(0, 0.4, 0));
}

vector<vector3d> suma(vector<vector3d> hierba, vector3d posicion)
{
	for(unsigned int i = 0; i < hierba.size(); i++)
	{
		hierba[i] = hierba[i] + posicion;
	}
	return hierba;
}

void IniciarHierba()
{
	InicializarHierba1();
	InicializarHierba2();
}

void CrearCesped(vector3d inicio, vector3d fin, vector<vector3d> &cesped)
{
    cout << inicio._x << ", " << inicio._y << ", " << inicio._z << endl;
    cout << fin._x << ", " << fin._y << ", " << fin._z << endl;

    for(float i = inicio._x; i < fin._x; i = i + 0.55)
    {
        for(float j = inicio._z; j < fin._z; j = j + 0.55)
        {
            srand(time(NULL));
            int tipo = 1 + ( rand() % ( 2 - 1 + 1 ) );
            
            vector<vector3d> hierba;
            
            if(tipo == 1)
            {
                hierba = suma(hierba1, vector3d(i, fin._y, j));
            }
            if(tipo == 2)
            {
                hierba = suma(hierba2, vector3d(i, fin._y, j));
            }
            cesped.insert(cesped.end(), hierba.begin(), hierba.end());
        }
    }
    //cout << inicio._x << ", " << inicio._y << ", " << inicio._z << endl;
}

int main()
{
    IniciarHierba();
    
    cout << "hola\n";
    
    vector3d inicio(0, 0, 0), fin(1, 0, 1);
    //cout << inicio._x << ", " << inicio._y << ", " << inicio._z << endl;
    //cout << fin._x << ", " << fin._y << ", " << fin._z << endl;
    vector<vector3d> cesped;
    CrearCesped(inicio, fin, cesped);
    
    cout << cesped.size() << endl;
    
    cout << "adios\n";
}
*/

#endif
