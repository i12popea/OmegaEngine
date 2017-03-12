#ifndef _QUATERNION_HPP_
#define _QUATERNION_HPP_

#include "vector3d.hpp"
#include <iostream>
#include <cmath>
#include <cstring>
#include <stdio.h>
#include <assert.h>

using namespace std;

namespace ed{

class quaternion
{
private:
	float _x;
	float _y;
	float _z;
	float _w;
public:
	//Constructor parametrizado
	quaternion(float x=0.0, float y=0.0, float z=0.0, float w=1.0)
	{
		setX(x);
		setY(y);
		setZ(z);
		setW(w);
	}
	//Constructor de copia
	quaternion(quaternion const &v)
	{
		setX(v.getX());
		setY(v.getY());
		setZ(v.getZ());
		setW(v.getW());
	}
	//Destructor
	~quaternion()
	{
		setX(0);
		setY(0);
		setZ(0);
		setW(1);
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
	inline void setW(float w)
	{
		_w=w;
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
	inline float getW()const
	{
		return _w;
	}

	quaternion & operator = (quaternion const &vector);
	void Quat_computeW();
	void Quat_normalize();

};

quaternion Quat_multQuat (const quaternion qa, const quaternion qb);
quaternion Quat_multVec (const quaternion q, const vector3d v);
vector3d Quat_rotatePoint (const quaternion q, const vector3d in);
float Quat_dotProduct (const quaternion qa, const quaternion qb);
void Quat_slerp (const quaternion qa, const quaternion qb, float t, quaternion &out);

}

#endif
