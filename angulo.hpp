#ifndef _ANGULO_HPP_
#define _ANGULO_HPP_

#include <iostream>
#include <GL/glut.h>

using namespace std;

namespace ed{

class Angulo
{
private:
	float _xrot;
	float _yrot;
public:
	Angulo(float xrot=0.0, float yrot=0.0)
	{
		setXrot(xrot);
		setYrot(yrot);
	};
	~Angulo(){};

	//Observadores
	inline float getXrot() const
	{
		return _xrot;
	}
	inline float getYrot() const
	{
		return _yrot;
	}
	//Modificadores
	inline void setXrot(float xrot)
	{
		_xrot = xrot;
	}
	inline void setYrot(float yrot)
	{
		_yrot = yrot;
	}
	
void mouseMovement(int x, int y);
	
};

}

#endif
