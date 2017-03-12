#include "angulo.hpp"

using namespace std;
using namespace ed;

bool warp = false;

namespace ed{

void Angulo::mouseMovement(int x, int y)
{
	int CenterX = glutGet(GLUT_WINDOW_WIDTH)/2;
	int CenterY = glutGet(GLUT_WINDOW_HEIGHT)/2;
	int diffx = x - CenterX;
	int diffy = y - CenterY;
	if(!warp)
	{
		warp = true;
		setXrot(getXrot() + (float)diffy*0.25f);//xrot += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
		setYrot(getYrot() + (float)diffx*0.25f);//yrot += (float) diffx; //set the xrot to yrot with the addition of the difference in the x position
		    
		if(getXrot() > 90.0)
			setXrot(90.0);
		else
			if(getXrot() < -90.0)
				setXrot(-90.0);
		if(getYrot() < 0.0)
			setYrot(getYrot() + 360.0);
		else
			if(getYrot() >= 360.0)
				setYrot(getYrot() - 360.0);
	}
	else
	{
		warp = false;
	}
}

}
