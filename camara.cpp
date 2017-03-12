#include "camara.hpp"

using namespace std;
using namespace ed;

namespace ed{

Camara & Camara::operator = (Camara const &camara)
{
	if(this != &camara)
	{
		_posicion.setX(camara.getVector().getX());
		_posicion.setY(camara.getVector().getY());
		_posicion.setZ(camara.getVector().getZ());

		_angulo.setXrot(camara._angulo.getXrot());
		_angulo.setYrot(camara._angulo.getYrot());
	}
	return *this;
}

void Camara::camara()
{
    glRotatef(_angulo.getXrot(),1.0,0.0,0.0);  //rotate our camera on teh x-axis (left and right)
    glRotatef(_angulo.getYrot(),0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-1 * _posicion.getX(),-1 * _posicion.getY(),-1 * _posicion.getZ());
    //glTranslated(-1 * setVector().getX(),-1 * setVector().getY(),-1 * setVector().getZ()); //translate the screen to the position of our camera
}

void Camara::avanzar(bool banderaY)
{
	float xrotrad, yrotrad;
	yrotrad = (_angulo.getYrot() / 180 * 3.141592654f);
	xrotrad = (_angulo.getXrot() / 180 * 3.141592654f);

	_posicion.setX(_posicion.getX() + float(sin(yrotrad)) * 0.5);
	_posicion.setZ(_posicion.getZ() - float(cos(yrotrad)) * 0.5);
	if(banderaY)
		_posicion.setY(_posicion.getY() - float(sin(xrotrad)) * 0.5);
    
    //setVector().setX(setVector().getX() + float(sin(yrotrad)));
    //setVector().setZ(setVector().getZ() - float(cos(yrotrad)));
    //setVector().setY(setVector().getY() - float(sin(xrotrad)));

    //xpos += float(sin(yrotrad));
    //zpos -= float(cos(yrotrad));
    //ypos -= float(sin(xrotrad));
}

void Camara::retroceder(bool banderaY)
{
	float xrotrad, yrotrad;
	yrotrad = (_angulo.getYrot() / 180 * 3.141592654f);
	xrotrad = (_angulo.getXrot() / 180 * 3.141592654f);

	_posicion.setX(_posicion.getX() - float(sin(yrotrad)) * 0.5);
	_posicion.setZ(_posicion.getZ() + float(cos(yrotrad)) * 0.5);
	if(banderaY)
		_posicion.setY(_posicion.getY() + float(sin(xrotrad)) * 0.5);
    
    //setVector().setX(setVector().getX() - float(sin(yrotrad)));
    //setVector().setZ(setVector().getZ() + float(cos(yrotrad)));
    //setVector().setY(setVector().getY() + float(sin(xrotrad)));

    //xpos -= float(sin(yrotrad));
    //zpos += float(cos(yrotrad));
    //ypos += float(sin(xrotrad));
}

void Camara::irDerecha()
{
    float yrotrad;
    yrotrad = (_angulo.getYrot() / 180 * 3.141592654f);

    _posicion.setX(_posicion.getX() + float(cos(yrotrad)) * 0.5);
    _posicion.setZ(_posicion.getZ() + float(sin(yrotrad)) * 0.5);
    
    //setVector().setX(setVector().getX() + float(cos(yrotrad)) * 0.2);
    //setVector().setZ(setVector().getZ() + float(sin(yrotrad)) * 0.2);

    //xpos += float(cos(yrotrad)) * 0.2;
    //zpos += float(sin(yrotrad)) * 0.2;
}

void Camara::irIzquierda()
{
    float yrotrad;
    yrotrad = (_angulo.getYrot() / 180 * 3.141592654f);

    _posicion.setX(_posicion.getX() - float(cos(yrotrad)) * 0.5);
    _posicion.setZ(_posicion.getZ() - float(sin(yrotrad)) * 0.5);
    
    //setVector().setX(setVector().getX() - float(cos(yrotrad)) * 0.2);
    //setVector().setZ(setVector().getZ() - float(sin(yrotrad)) * 0.2);

    //xpos -= float(cos(yrotrad)) * 0.2;
    //zpos -= float(sin(yrotrad)) * 0.2;
}

}
