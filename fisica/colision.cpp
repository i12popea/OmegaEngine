#include "colision.hpp"

using namespace std;
using namespace ed;

namespace ed{

float distanciaX(Esfera uno, Esfera dos)
{
	float distanciaX=dos.getVector3d().getX() - uno.getVector3d().getX();
	if(distanciaX < 0)
		return -distanciaX;
	return distanciaX;
}

float distanciaY(Esfera uno, Esfera dos)
{
	float distanciaY=dos.getVector3d().getY() - uno.getVector3d().getY();
	if(distanciaY < 0)
		return -distanciaY;
	return distanciaY;
}

float distanciaZ(Esfera uno, Esfera dos)
{
	float distanciaZ=dos.getVector3d().getZ() - uno.getVector3d().getZ();
	if(distanciaZ < 0)
		return -distanciaZ;
	return distanciaZ;
}

float distanciaX(vector3d uno, vector3d dos)
{
	float distanciaX=dos.getX() - uno.getX();
	if(distanciaX < 0)
		return -distanciaX;
	return distanciaX;
}

float distanciaY(vector3d uno, vector3d dos)
{
	float distanciaY=dos.getY() - uno.getY();
	if(distanciaY < 0)
		return -distanciaY;
	return distanciaY;
}

float distanciaZ(vector3d uno, vector3d dos)
{
	float distanciaZ=dos.getZ() - uno.getZ();
	if(distanciaZ < 0)
		return -distanciaZ;
	return distanciaZ;
}

float distancia(Esfera uno, Esfera dos)
{
	float distancia=sqrt(pow(distanciaX(uno, dos), 2) + pow(distanciaY(uno, dos), 2) + pow(distanciaZ(uno, dos), 2));
	return distancia;
}

float distanciaEntrePuntos(vector3d uno, vector3d dos)
{
	float distancia=sqrt(pow(uno.getX()-dos.getX(), 2) + pow(uno.getY()-dos.getY(), 2) + pow(uno.getZ()-dos.getZ(), 2));
	return distancia;
}

float distanciaEntrePuntos2D(vector3d uno, vector3d dos)
{
	float distancia=sqrt(pow(uno.getX()-dos.getX(), 2) + pow(uno.getZ()-dos.getZ(), 2));
	return distancia;
}

bool interseccion (Esfera esferaUno, Esfera esferaDos)
{
	if(distancia(esferaUno, esferaDos) <= (esferaUno.getRadio() + esferaDos.getRadio()))
		return true;
	return false;
}

//Función de interseccion entre dos boxes
bool interseccion (Box obj1, Box obj2)
{
	if(abs(obj1.getVector3d().getX() - obj2.getVector3d().getX()) <= obj1.getAncho() + obj2.getAncho())
	{
		if(abs(obj1.getVector3d().getY() - obj2.getVector3d().getY()) <= obj1.getAlto() + obj2.getAlto())
		{
			if(abs(obj1.getVector3d().getZ() - obj2.getVector3d().getZ()) <= obj1.getLargo() + obj2.getLargo())
				return true;
		}
	}
	return false;
}

/*Funcion de interseccion entre una esfera y un punto*/
bool interseccion(Esfera esfera, vector3d punto)
{
	if(distanciaEntrePuntos(esfera.getVector3d(), punto) <= esfera.getRadio())
		return true;
	return false;
}

/*Funcion de interseccion entre un cubo y un punto*/
bool interseccion(Box cubo, vector3d punto)
{
	float distX = distanciaX(cubo.getVector3d(), punto);
	float distY = distanciaY(cubo.getVector3d(), punto);
	float distZ = distanciaZ(cubo.getVector3d(), punto);
	
	if((distX <= cubo.getLargo()) && (distY <= cubo.getAlto()) && (distZ <= cubo.getAncho()))
		return true;
	return false;
}

/*Funcion de interseccion entre una esfera y un cubo*/
bool interseccion(Esfera esfera, Box cubo)
{
	bool banderaX = false, banderaY = false, banderaZ = false;
	float distanciaX = abs(abs(esfera.getVector3d().getX() - cubo.getVector3d().getX()) - cubo.getAncho()/2);
	float distanciaY = abs(abs(esfera.getVector3d().getY() - cubo.getVector3d().getY()) - cubo.getAlto()/2);
	float distanciaZ = abs(abs(esfera.getVector3d().getZ() - cubo.getVector3d().getZ()) - cubo.getLargo()/2);

	if(distanciaX > (cubo.getAncho()/2 + esfera.getRadio()))
		return false;
	if(distanciaY > (cubo.getAlto()/2 + esfera.getRadio()))
		return false;
	if(distanciaZ > (cubo.getLargo()/2 + esfera.getRadio()))
		return false;

	if(distanciaX <= (cubo.getAncho()/2))
		banderaX = true;
		//return true;
	if(distanciaY <= (cubo.getAlto()/2))
		banderaY = true;
		//return true;
	if(distanciaZ <= (cubo.getLargo()/2))
		banderaZ = true;
		//return true;

	if((banderaX) && (banderaY) && (banderaZ))
		return true;
	//return false;

	float distanciaEsquina = pow(distanciaX - cubo.getAncho()/2, 2) + pow(distanciaY - cubo.getAlto()/2, 2) + pow(distanciaZ - cubo.getLargo()/2, 2);
	return (distanciaEsquina <= (pow(esfera.getRadio(), 2)));
}

bool ColisionCilindroEsfera(Esfera esfera, Cilindro cilindro, bool &colSuelo, bool &colTecho, bool &colPared, float &difX, float &difZ)
{
	float distanciaX = abs(esfera.getVector3d().getX() - cilindro.getVector3d().getX());
	float distanciaZ = abs(esfera.getVector3d().getZ() - cilindro.getVector3d().getZ());
	colSuelo = false; colTecho = false; colPared = false;

	if(sqrt(pow(distanciaX, 2) + pow(distanciaZ, 2)) <= esfera.getRadio() + cilindro.getRadio())
	{
		if( (esfera.getVector3d().getY() > cilindro.getVector3d().getY() + cilindro.getAltura()) || (esfera.getVector3d().getY() < cilindro.getVector3d().getY() - cilindro.getAltura()) )
			return false;
		else
		{
			if( (esfera.getVector3d().getY() < cilindro.getVector3d().getY() + cilindro.getAltura()) && (esfera.getVector3d().getY() > cilindro.getVector3d().getY() - cilindro.getAltura()) )
			{
				colSuelo = false; colTecho = false; colPared = true;
				return true;
			}
			else
			{
				Esfera esferaA(vector3d(cilindro.getVector3d().getX(), cilindro.getVector3d().getY() + cilindro.getAltura(), cilindro.getVector3d().getZ()), cilindro.getRadio());
				Esfera esferaB(vector3d(cilindro.getVector3d().getX(), cilindro.getVector3d().getY() - cilindro.getAltura(), cilindro.getVector3d().getZ()), cilindro.getRadio());
				if(interseccion(esfera, esferaA))
				{
					if((esfera.getVector3d().getY() - esfera.getRadio()) <= esferaA.getVector3d().getY())
					{
						colSuelo = false; colTecho = true; colPared = false;
						return true;
					}
					else
						return false;
					//return ((esfera.getVector3d().getY() - esfera.getRadio()) <= esferaA.getVector3d().getY());
				}
				if(interseccion(esfera, esferaB))
				{
					if((esfera.getVector3d().getY() - esfera.getRadio()) >= esferaB.getVector3d().getY())
					{
						colSuelo = true; colTecho = false; colPared = false;
						return true;
					}
					else
						return false;
					//return ((esfera.getVector3d().getY() - esfera.getRadio()) >= esferaB.getVector3d().getY());
				}
			}
		}
	}
	return false;
}

void ReaccionCilindroEsfera(vector3d &posicion, bool colSuelo, bool colTecho, bool colPared, Esfera esfera, Cilindro cilindro, float difX, float difZ)
{
	float distanciaX = cilindro.getVector3d().getX() - esfera.getVector3d().getX();
	float distanciaZ = cilindro.getVector3d().getZ() - esfera.getVector3d().getZ();
	if(colSuelo)
		posicion.setY(esfera.getVector3d().getY() + esfera.getRadio() + cilindro.getAltura()*2);
	if(colTecho)
		posicion.setY(esfera.getVector3d().getY() - esfera.getRadio() - 0.0001);
	if(colPared)
	{
		/*if(abs(difX) <= esfera.getRadio()/2)	//Si hay colision desde el eje X se corrige el eje Z
		{
			if(difZ < 0)	//Se necesita saber si es mayor o menor que 0 para saber la orientación correcta
				posicion.setZ(esfera.getVector3d().getZ() - esfera.getRadio() - cilindro.getRadio() - 0.5);
			else		//Si es mayor que 0
				posicion.setZ(esfera.getVector3d().getZ() + esfera.getRadio() + cilindro.getRadio() + 0.5);
		}
		if(abs(difZ) <= esfera.getRadio()/2)	//Si hay colision desde el eje Z se corrige el eje X
		{
			if(difX < 0)
				posicion.setX(esfera.getVector3d().getX() - esfera.getRadio() - cilindro.getRadio() - 0.5);
			else
				posicion.setX(esfera.getVector3d().getX() + esfera.getRadio() + cilindro.getRadio() + 0.5);
		}*/
		if(distanciaX < 0 && distanciaX < distanciaZ)
			posicion.setX(esfera.getVector3d().getX() - esfera.getRadio() - cilindro.getRadio() - 0.5);
		else if(distanciaX > 0 && distanciaX > distanciaZ)
			posicion.setX(esfera.getVector3d().getX() + esfera.getRadio() + cilindro.getRadio() + 0.5);
		if(distanciaZ < 0 && distanciaZ < distanciaX)
			posicion.setZ(esfera.getVector3d().getZ() - esfera.getRadio() - cilindro.getRadio() - 0.5);
		else if(distanciaZ > 0 && distanciaZ > distanciaX)
			posicion.setZ(esfera.getVector3d().getZ() + esfera.getRadio() + cilindro.getRadio() + 0.5);
	}
}

/*bool ColisionCilindroOcteto(Box octeto, Cilindro cilindro, bool &colSuelo, bool &colTecho, bool &colPared, float &difX, float &difZ)
{
	float distanciaAltura = abs(cilindro.getVector3d().getY() - octeto.getVector3d().getY());

	float distanciaX = abs(abs(cilindro.getVector3d().getX() - octeto.getVector3d().getX()) - octeto.getAncho()/2);
	float distanciaZ = abs(abs(cilindro.getVector3d().getZ() - octeto.getVector3d().getZ()) - octeto.getLargo()/2);

	difX = cilindro.getVector3d().getX() - octeto.getVector3d().getX() - octeto.getAncho()/2;
	difZ = cilindro.getVector3d().getZ() - octeto.getVector3d().getZ() - octeto.getLargo()/2;

	colSuelo = false; colTecho = false; colPared = false;

	if(distanciaX > (octeto.getAncho()/2 + cilindro.getRadio()))
		return false;
	if(distanciaZ > (octeto.getLargo()/2 + cilindro.getRadio()))
		return false;

	if( (distanciaX <= (octeto.getAncho()/2)) && (distanciaAltura <= (cilindro.getAltura() + octeto.getAlto())) )
	{
		if( ((octeto.getVector3d().getY() - octeto.getAlto()) <= cilindro.getVector3d().getY() + cilindro.getAltura()) && ((octeto.getVector3d().getY() - octeto.getAlto()) > cilindro.getVector3d().getY() + cilindro.getAltura()*0.50) )
		//if( ((octeto.getVector3d().getY() - octeto.getAlto()) <= cilindro.getVector3d().getY() + cilindro.getAltura()) && ((octeto.getVector3d().getY() - octeto.getAlto()) > cilindro.getVector3d().getY() + cilindro.getAltura()*0.80) )
			colTecho = true;
		else if( ((octeto.getVector3d().getY() + octeto.getAlto()) >= cilindro.getVector3d().getY() - cilindro.getAltura()) && ((octeto.getVector3d().getY() + octeto.getAlto()) < cilindro.getVector3d().getY() - cilindro.getAltura()*0.50) )
		//else if( ((octeto.getVector3d().getY() + octeto.getAlto()) >= cilindro.getVector3d().getY() - cilindro.getAltura()) && ((octeto.getVector3d().getY() + octeto.getAlto()) < cilindro.getVector3d().getY() - cilindro.getAltura()*0.90) )
			colSuelo = true;
		else
			colPared = true;
		return true;
	}
	if( (distanciaZ <= (octeto.getLargo()/2)) && (distanciaAltura <= (cilindro.getAltura() + octeto.getAlto())) )
	{
		if( ((octeto.getVector3d().getY() - octeto.getAlto()) <= cilindro.getVector3d().getY() + cilindro.getAltura()) && ((octeto.getVector3d().getY() - octeto.getAlto()) > cilindro.getVector3d().getY() + cilindro.getAltura()*0.50) )
		//if( ((octeto.getVector3d().getY() - octeto.getAlto()) <= cilindro.getVector3d().getY() + cilindro.getAltura()) && ((octeto.getVector3d().getY() - octeto.getAlto()) > cilindro.getVector3d().getY() + cilindro.getAltura()*0.80) )
			colTecho = true;
		else if( ((octeto.getVector3d().getY() + octeto.getAlto()) >= cilindro.getVector3d().getY() - cilindro.getAltura()) && ((octeto.getVector3d().getY() + octeto.getAlto()) < cilindro.getVector3d().getY() - cilindro.getAltura()*0.50) )
		//else if( ((octeto.getVector3d().getY() + octeto.getAlto()) >= cilindro.getVector3d().getY() - cilindro.getAltura()) && ((octeto.getVector3d().getY() + octeto.getAlto()) < cilindro.getVector3d().getY() - cilindro.getAltura()*0.90) )
			colSuelo = true;
		else
			colPared = true;
		return true;
	}

	float distanciaEsquina = pow(distanciaX - octeto.getAncho()/2, 2) + pow(distanciaZ - octeto.getLargo()/2, 2);
 
	if( (distanciaEsquina <= (pow(cilindro.getRadio(), 2))) && (distanciaAltura <= (cilindro.getAltura() + octeto.getAlto())) )
	{
		if( ((octeto.getVector3d().getY() - octeto.getAlto()) <= cilindro.getVector3d().getY() + cilindro.getAltura()) && ((octeto.getVector3d().getY() - octeto.getAlto()) > cilindro.getVector3d().getY() + cilindro.getAltura()*0.50) )
		//if( ((octeto.getVector3d().getY() - octeto.getAlto()) <= cilindro.getVector3d().getY() + cilindro.getAltura()) && ((octeto.getVector3d().getY() - octeto.getAlto()) > cilindro.getVector3d().getY() + cilindro.getAltura()*0.80) )
			colTecho = true;
		else if( ((octeto.getVector3d().getY() + octeto.getAlto()) >= cilindro.getVector3d().getY() - cilindro.getAltura()) && ((octeto.getVector3d().getY() + octeto.getAlto()) < cilindro.getVector3d().getY() - cilindro.getAltura()*0.50) )
		//else if( ((octeto.getVector3d().getY() + octeto.getAlto()) >= cilindro.getVector3d().getY() - cilindro.getAltura()) && ((octeto.getVector3d().getY() + octeto.getAlto()) < cilindro.getVector3d().getY() - cilindro.getAltura()*0.90) )
			colSuelo = true;
		else
			colPared = true;
		return true;
	}
	else
	{
		colTecho = false; colSuelo = false; colPared = false;
		return false;
	}
}*/
bool ColisionCilindroOcteto(Box octeto, Cilindro cilindro, bool &colSuelo, bool &colTecho, bool &colPared, float &difX, float &difZ)
{
	float distanciaAltura = abs(cilindro.getVector3d().getY() - octeto.getVector3d().getY());

	float distanciaX = abs(abs(cilindro.getVector3d().getX() - octeto.getVector3d().getX()) - octeto.getAncho()/2);
	float distanciaZ = abs(abs(cilindro.getVector3d().getZ() - octeto.getVector3d().getZ()) - octeto.getLargo()/2);

	difX = cilindro.getVector3d().getX() - octeto.getVector3d().getX() - octeto.getAncho()/2;
	difZ = cilindro.getVector3d().getZ() - octeto.getVector3d().getZ() - octeto.getLargo()/2;

	colSuelo = false; colTecho = false; colPared = false;

	if(distanciaX > (octeto.getAncho()/2 + cilindro.getRadio()))
		return false;
	if(distanciaZ > (octeto.getLargo()/2 + cilindro.getRadio()))
		return false;

	if( (distanciaX <= (octeto.getAncho()/2)) && (distanciaAltura <= (cilindro.getAltura() + octeto.getAlto())) )
	{
		if( ((octeto.getVector3d().getY() - octeto.getAlto()) <= cilindro.getVector3d().getY() + cilindro.getAltura()) && ((octeto.getVector3d().getY() - octeto.getAlto()) > cilindro.getVector3d().getY() + cilindro.getAltura()*0.50) )
			colTecho = true;
		else if( ((octeto.getVector3d().getY() + octeto.getAlto()) >= cilindro.getVector3d().getY() - cilindro.getAltura()) && ((octeto.getVector3d().getY() + octeto.getAlto()) < cilindro.getVector3d().getY() - cilindro.getAltura()*0.50) )
			colSuelo = true;
		else
			colPared = true;
		return true;
	}
	if( (distanciaZ <= (octeto.getLargo()/2)) && (distanciaAltura <= (cilindro.getAltura() + octeto.getAlto())) )
	{
		if( ((octeto.getVector3d().getY() - octeto.getAlto()) <= cilindro.getVector3d().getY() + cilindro.getAltura()) && ((octeto.getVector3d().getY() - octeto.getAlto()) > cilindro.getVector3d().getY() + cilindro.getAltura()*0.50) )
			colTecho = true;
		else if( ((octeto.getVector3d().getY() + octeto.getAlto()) >= cilindro.getVector3d().getY() - cilindro.getAltura()) && ((octeto.getVector3d().getY() + octeto.getAlto()) < cilindro.getVector3d().getY() - cilindro.getAltura()*0.50) )
			colSuelo = true;
		else
			colPared = true;
		return true;
	}

	float distanciaEsquina = pow(distanciaX - octeto.getAncho()/2, 2) + pow(distanciaZ - octeto.getLargo()/2, 2);
 
	if( (distanciaEsquina <= (pow(cilindro.getRadio(), 2))) && (distanciaAltura <= (cilindro.getAltura() + octeto.getAlto())) )
	{
		if( ((octeto.getVector3d().getY() - octeto.getAlto()) <= cilindro.getVector3d().getY() + cilindro.getAltura()) && ((octeto.getVector3d().getY() - octeto.getAlto()) > cilindro.getVector3d().getY() + cilindro.getAltura()*0.50) )
			colTecho = true;
		else if( ((octeto.getVector3d().getY() + octeto.getAlto()) >= cilindro.getVector3d().getY() - cilindro.getAltura()) && ((octeto.getVector3d().getY() + octeto.getAlto()) < cilindro.getVector3d().getY() - cilindro.getAltura()*0.50) )
			colSuelo = true;
		else
			colPared = true;
		return true;
	}
	else
	{
		colTecho = false; colSuelo = false; colPared = false;
		return false;
	}
}
void ReaccionCilindroOcteto(vector3d &posicion, bool colSuelo, bool colTecho, bool colPared, Box octeto, Cilindro cilindro, float difX, float difZ)
{
	float distanciaX = abs(abs(cilindro.getVector3d().getX() - octeto.getVector3d().getX()) - octeto.getAncho()/2);
	float distanciaZ = abs(abs(cilindro.getVector3d().getZ() - octeto.getVector3d().getZ()) - octeto.getLargo()/2);
	float distanciaEsquina = pow(abs(distanciaX) - octeto.getAncho()/2, 2) + pow(abs(distanciaZ) - octeto.getLargo()/2, 2);
	if(colSuelo)
		posicion.setY(octeto.getVector3d().getY() + octeto.getAlto() + cilindro.getAltura()*2);
	if(colTecho)
		posicion.setY(octeto.getVector3d().getY() - octeto.getAlto() - 0.0001);
	if(colPared)
	{
		if( (cilindro.getVector3d().getX() >= octeto.getVector3d().getX() - octeto.getAncho()) && (cilindro.getVector3d().getX() <= octeto.getVector3d().getX() + octeto.getAncho()) && (cilindro.getVector3d().getZ() + cilindro.getRadio() >= octeto.getVector3d().getZ()) )
			posicion.setZ(octeto.getVector3d().getZ() + octeto.getLargo() + cilindro.getRadio() + 0.5);
		else if( (cilindro.getVector3d().getX() >= octeto.getVector3d().getX() - octeto.getAncho()) && (cilindro.getVector3d().getX() <= octeto.getVector3d().getX() + octeto.getAncho()) && (cilindro.getVector3d().getZ() - cilindro.getRadio() <= octeto.getVector3d().getZ()) )
			posicion.setZ(octeto.getVector3d().getZ() - octeto.getLargo() - cilindro.getRadio() - 0.5);
		else if( (cilindro.getVector3d().getZ() >= octeto.getVector3d().getZ() - octeto.getLargo()) && (cilindro.getVector3d().getZ() <= octeto.getVector3d().getZ() + octeto.getLargo()) && (cilindro.getVector3d().getX() + cilindro.getRadio() >= octeto.getVector3d().getX()) )
			posicion.setX(octeto.getVector3d().getX() + octeto.getAncho() + cilindro.getRadio() + 0.5);
		else if( (cilindro.getVector3d().getZ() >= octeto.getVector3d().getZ() - octeto.getLargo()) && (cilindro.getVector3d().getZ() <= octeto.getVector3d().getZ() + octeto.getLargo()) && (cilindro.getVector3d().getX() - cilindro.getRadio() <= octeto.getVector3d().getX()) )
			posicion.setX(octeto.getVector3d().getX() - octeto.getAncho() - cilindro.getRadio() - 0.5);

		/*if( (cilindro.getVector3d().getX() >= octeto.getVector3d().getX() - octeto.getAncho()) && (cilindro.getVector3d().getX() <= octeto.getVector3d().getX() + octeto.getAncho()) )
		{
			if(cilindro.getVector3d().getZ() + cilindro.getRadio() >= octeto.getVector3d().getZ())
				posicion.setZ(octeto.getVector3d().getZ() + octeto.getLargo() + cilindro.getRadio() + 0.5);
			else
				posicion.setZ(octeto.getVector3d().getZ() - octeto.getLargo() - cilindro.getRadio() - 0.5);
		}
		else
		{
			if(cilindro.getVector3d().getX() + cilindro.getRadio() >= octeto.getVector3d().getX())
				posicion.setX(octeto.getVector3d().getX() + octeto.getAncho() + cilindro.getRadio() + 0.5);
			else
				posicion.setX(octeto.getVector3d().getX() - octeto.getAncho() - cilindro.getRadio() - 0.5);
		}*/

		else{
			if(distanciaEsquina <= pow(cilindro.getRadio(), 2))
			{
				if(difX < 0 && difZ < 0)
				{
					posicion.setX(octeto.getVector3d().getX() - octeto.getAncho() - cilindro.getRadio());
					posicion.setZ(octeto.getVector3d().getZ() - octeto.getLargo() - cilindro.getRadio());
				}
				if(difX < 0 && difZ > 0)
				{
					posicion.setX(octeto.getVector3d().getX() - octeto.getAncho() - cilindro.getRadio());
					posicion.setZ(octeto.getVector3d().getZ() + octeto.getLargo() + cilindro.getRadio());
				}
				if(difX > 0 && difZ < 0)
				{
					posicion.setX(octeto.getVector3d().getX() + octeto.getAncho() + cilindro.getRadio());
					posicion.setZ(octeto.getVector3d().getZ() - octeto.getLargo() - cilindro.getRadio());
				}
				if(difX > 0 && difZ > 0)
				{
					posicion.setX(octeto.getVector3d().getX() + octeto.getAncho() + cilindro.getRadio());
					posicion.setZ(octeto.getVector3d().getZ() + octeto.getLargo() + cilindro.getRadio());
				}
			}
		}
	}
}

/*void ReaccionCilindroOcteto(vector3d &posicion, bool colSuelo, bool colTecho, bool colPared, Box octeto, Cilindro cilindro, float difX, float difZ)
{
	float distanciaX = abs(abs(cilindro.getVector3d().getX() - octeto.getVector3d().getX()) - octeto.getAncho()/2);
	float distanciaZ = abs(abs(cilindro.getVector3d().getZ() - octeto.getVector3d().getZ()) - octeto.getLargo()/2);
	float distanciaEsquina = pow(abs(distanciaX) - octeto.getAncho()/2, 2) + pow(abs(distanciaZ) - octeto.getLargo()/2, 2);
	if(colSuelo)
		posicion.setY(octeto.getVector3d().getY() + octeto.getAlto() + cilindro.getAltura()*2);
	if(colTecho)
		posicion.setY(octeto.getVector3d().getY() - octeto.getAlto() - 0.0001);
	if(colPared)
	{
		if(distanciaZ <= octeto.getLargo()/2)
		{
			if((difX < 0) && (difX < difZ))	//Si hay colision desde el eje X se corrige el eje Z
				posicion.setX(octeto.getVector3d().getX() - octeto.getAncho() - cilindro.getRadio() - 0.5);
			else if((difX > 0) && (difX > difZ))
				posicion.setX(octeto.getVector3d().getX() + octeto.getAncho() + cilindro.getRadio() + 0.5);
		}
		else if(distanciaX <= octeto.getAncho()/2)
		{
			if((difZ < 0) && (difZ < difX))	//Si hay colision desde el eje Z se corrige el eje X
				posicion.setZ(octeto.getVector3d().getZ() - octeto.getLargo() - cilindro.getRadio() - 0.5);
			else if((difZ > 0) && (difZ > difX))
				posicion.setZ(octeto.getVector3d().getZ() + octeto.getLargo() + cilindro.getRadio() + 0.5);
		}
		else if(distanciaEsquina <= pow(cilindro.getRadio(), 2))
		{
			if(difX < 0 && difZ < 0)
			{
				posicion.setX(octeto.getVector3d().getX() - octeto.getAncho() - cilindro.getRadio());
				posicion.setZ(octeto.getVector3d().getZ() - octeto.getLargo() - cilindro.getRadio());
			}
			if(difX < 0 && difZ > 0)
			{
				posicion.setX(octeto.getVector3d().getX() - octeto.getAncho() - cilindro.getRadio());
				posicion.setZ(octeto.getVector3d().getZ() + octeto.getLargo() + cilindro.getRadio());
			}
			if(difX > 0 && difZ < 0)
			{
				posicion.setX(octeto.getVector3d().getX() + octeto.getAncho() + cilindro.getRadio());
				posicion.setZ(octeto.getVector3d().getZ() - octeto.getLargo() - cilindro.getRadio());
			}
			if(difX > 0 && difZ > 0)
			{
				posicion.setX(octeto.getVector3d().getX() + octeto.getAncho() + cilindro.getRadio());
				posicion.setZ(octeto.getVector3d().getZ() + octeto.getLargo() + cilindro.getRadio());
			}
		}
	}
}*/

}
