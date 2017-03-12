#include "colisionCubo.hpp"

using namespace std;
using namespace ed;

namespace ed{

Box::Box(vector3d vector, float alto, float largo, float ancho)
{
	setVector3d(vector);
	setAlto(alto);
	setLargo(largo);
	setAncho(ancho);
}

Box& Box::operator = (const Box &box)
{
	if(this != &box)
	{
		_coordenadas = box._coordenadas;
		setAlto(box.getAlto());
		setLargo(box.getLargo());
		setAncho(box.getAncho());
	}
	return *this;
}

vector<vector3d> Box::trianguloBox()
{
	vector<vector3d> box;
/*//Suelo
	box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); //Cara 1

	box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); //Cara 2
//Techo
	box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); //Cara 3

	box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); //Cara 4
//Lateral 1
	box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); //Cara 5 (Mal)

	box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); //Cara 6 (Bien)
//Frontal
	box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); //Cara 7 (Mal)

	box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); //Cara 8 (Bien)
//Lateral 2
	box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); //Cara 9 (Mal)

	box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); //Cara 10 (Bien)
//Posterior
	box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); //Cara 11 (Mal)

	box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); //Cara 12 (Bien)*/

	/*box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - (getAlto() + 0.50000), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - (getAlto() + 0.50000), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - (getAlto() + 0.50000), _coordenadas.getZ() - getLargo())); //Cara 1
	box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - (getAlto() + 0.50000), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - (getAlto() + 0.50000), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - (getAlto() + 0.50000), _coordenadas.getZ() - getLargo())); //Cara 2*/


//Suelo
	box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); //Cara 1

	box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); //Cara 2

//Techo
	box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); //Cara 3

	box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); //Cara 4

//Lateral 1
	box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); //Cara 5 (Mal)

	box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); //Cara 6 (Bien)

//Frontal
	box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); //Cara 7 (Mal)

	box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); //Cara 8 (Bien)

//Lateral 2
	box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); //Cara 9 (Mal)

	box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); //Cara 10 (Bien)

//Posterior
	box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() - getAlto(), _coordenadas.getZ() + getLargo())); //Cara 11 (Mal)

	box.push_back(vector3d(_coordenadas.getX() + getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() - getLargo())); box.push_back(vector3d(_coordenadas.getX() - getAncho(), _coordenadas.getY() + getAlto(), _coordenadas.getZ() + getLargo())); //Cara 12 (Bien)

	return box;
}

vector3d Box::getVertexP(vector3d &normal)
{
	vector3d res = _coordenadas;

	if (normal.getX() > 0)
		res.setX(res.getX() + _ancho);

	if (normal.getY() > 0)
		res.setY(res.getY() + _alto);

	if (normal.getZ() > 0)
		res.setZ(res.getZ() + _largo);

	return(res);
}

vector3d Box::getVertexN(vector3d &normal)
{
	vector3d res = _coordenadas;

	if (normal.getX() < 0)
		res.setX(res.getX() + _ancho);

	if (normal.getY() < 0)
		res.setY(res.getY() + _alto);

	if (normal.getZ() < 0)
		res.setZ(res.getZ() + _largo);

	return(res);
}

}
