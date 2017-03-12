#include "indicePlano.hpp"

using namespace std;
using namespace ed;

namespace ed{

IndicePlano::IndicePlano(int a, int b, int c)
{
	setPuntoA(a);
	setPuntoB(b);
	setPuntoC(c);
}

/**/
/*bool interseccion (Plano plano, vector3d vector)
{
	//Realizamos la distancia del vector respecto al plano triangular
	float distanciaPlano = ecuacionPlano(plano, vector);

	//Realizamos las opreaciones para saber si el vector se sale del plano dividiendolo en dos triangulos
	//Rectas del triangulo
	float X, Y, Z;
	float recta1, recta2 recta3;
	
	X = plano.getVector3d()[0].getX() - plano.getVector3d()[1].getX();
	Y = plano.getVector3d()[0].getY() - plano.getVector3d()[1].getY();
	Z = plano.getVector3d()[0].getZ() - plano.getVector3d()[1].getZ();
	
	//Primera ecuacion
	if(Y >= Z) //Pared
        recta1 = ecuacionRectaDosPuntos(plano.getVector3d()[0], plano.getVector3d()[1], vector, 1);
    else if(Z < Y) //Suelo
        recta1 = ecuacionRectaDosPuntos(plano.getVector3d()[0], plano.getVector3d()[1], vector, 0);
	
	X = plano.getVector3d()[1].getX() - plano.getVector3d()[2].getX();
	Y = plano.getVector3d()[1].getY() - plano.getVector3d()[2].getY();
	Z = plano.getVector3d()[1].getZ() - plano.getVector3d()[2].getZ();
	
	//Segunda ecuacion
	if(Y >= Z) //Pared
	    recta2 = ecuacionRectaDosPuntos(plano.getVector3d()[1], plano.getVector3d()[2], vector, 1);
    else if(Z < Y) //Suelo
        recta2 = ecuacionRectaDosPuntos(plano.getVector3d()[1], plano.getVector3d()[2], vector, 0);
	
	X = plano.getVector3d()[2].getX() - plano.getVector3d()[0].getX();
	Y = plano.getVector3d()[2].getY() - plano.getVector3d()[0].getY();
	Z = plano.getVector3d()[2].getZ() - plano.getVector3d()[0].getZ();
	
	//Tercera ecuacion
	if(Y >= Z) //Pared
	    recta3 = ecuacionRectaDosPuntos(plano.getVector3d()[2], plano.getVector3d()[0], vector, 1);
    else if(Z < Y) //Suelo
        recta3 = ecuacionRectaDosPuntos(plano.getVector3d()[2], plano.getVector3d()[0], vector, 0);

	if((distanciaPlano == 0.0) && (vector.getZ() > recta1) || (vector.getZ() > recta2) || (vector.getZ() > recta3)) //Si se sale de los limites del triangulo hay colision
		return true;

	return false; //Si no hay colision se devuelve false
}*/

//Calcular ecuacion de la recta: http://www.vitutor.com/geo/rec/d_7.html



}
