#ifndef _VECTOR3D_HPP_
#define _VECTOR3D_HPP_

#include <iostream>
#include <cmath>

using namespace std;

namespace ed{

class vector3d
{
private:
	float _x;
	float _y;
	float _z;
public:
	//Constructor parametrizado
	vector3d(float x=0.0, float y=0.0, float z=0.0)
	{
		setX(x);
		setY(y);
		setZ(z);
	}
	//Constructor de copia
	vector3d(vector3d const &v)
	{
		setX(v.getX());
		setY(v.getY());
		setZ(v.getZ());
	}
	//Destructor
	~vector3d()
	{
		setX(0);
		setY(0);
		setZ(0);
	}

	//Modificadores
	inline void setX(float x)
	{
		_x=x;
	}
	inline void setY(float y)
	{
		_y=y;
	}
	inline void setZ(float z)
	{
		_z=z;
	}

	//Observadores
	inline float getX()const
	{
		return _x;
	}
	inline float getY()const
	{
		return _y;
	}
	inline float getZ()const
	{
		return _z;
	}


	//Sobrecargas
	vector3d operator + (vector3d const &vector);
	vector3d operator - (vector3d const &vector);
	vector3d operator * (int numero);
	vector3d operator * (float numero);
	vector3d operator / (int numero);
	vector3d & operator = (vector3d const &vector);
	bool operator == (vector3d const &vector);
	bool operator != (vector3d const &vector);
	friend std::ostream &operator << (std::ostream &stream, const vector3d &vector);

	//Funciones
	void setVector(float x, float y, float z);
	void setVector(vector3d vector);
	float productoEscalar(const vector3d &vector);
	vector3d productoVectorial(const vector3d &vector);
	float modulo();
	float modulo(vector3d vector);
	float modulo(vector3d vector1, vector3d vector2);
	void normalizarVector();
};

vector3d productoVectorial(const vector3d &vector1, const vector3d &vector2);
float productoEscalar(const vector3d &vector1, const vector3d &vector2);
float modulo(vector3d vector);
vector3d normalizarVector(vector3d vector);

class vector2d{
private:
	float _u;
	float _v;
public:
	//Constructor parametrizado
	vector2d(float u=0.0, float v=0.0)
	{
		setU(u);
		setV(v);
	}

	//Constructor de copia
	vector2d(vector2d const &vector)
	{
		setU(vector.getU());
		setV(vector.getV());
	}

	//Modificadores
	inline void setU(float u)
	{
		_u = u;
	}
	inline void setV(float v)
	{
		_v = v;
	}

	//Oservadores
	inline float getU()const
	{
		return _u;
	}
	inline float getV()const
	{
		return _v;
	}

	//Sobrecarga
	vector2d & operator = (vector2d const &vector);
};

}

#endif
