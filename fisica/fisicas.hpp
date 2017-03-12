#ifndef _FISICAS_HPP_
#define _FISICAS_HPP_

#include "../vector3d.hpp"
#include <vector>
#include <GL/glut.h>

using namespace std;
using std::vector;

#define GRAVEDAD_TIERRA 9.807;
#define GRAVEDAD_LUNA 1.622;
#define GRAVEDAD_MARTE 3.711;
#define GRAVEDAD_JUPITER 24.79;
#define GRAVEDAD_VENUS 8.87;
#define GRAVEDAD_SATURNO 10.44;
#define GRAVEDAD_MERCURIO 3.7;
#define GRAVEDAD_NEPTUNO 11.15;
#define GRAVEDAD_URANO 8.69;
#define GRAVEDAD_PLUTON 0.658;
#define GRAVEDAD_TITAN 1.352;

namespace ed{

class Particula
{
private:
	vector3d _posicion;
	vector3d _velocidad;
	vector3d _gravedad;
	vector3d _fuerza;
	float _masa;
public:
	inline vector3d getVector3d()
	{
		return _posicion;
	}
	inline vector3d getVelocidad()
	{
		return _velocidad;
	}
	inline vector3d getGravedad()
	{
		return _gravedad;
	}
	inline vector3d getFuerza()
	{
		return _fuerza;
	}
	inline float getMasa()
	{
		return _masa;
	}

	void Actualizar();
};

float gravedad(vector3d posicion1, vector3d posicion2, float masa1, float masa2, float constanteGravedad);
float velocidadAceleracion(float fuerza, float masa);
float CapturaFrames();
float CaidaLibre(float tiempo, float velInicial, float gravedad, float posInicial);
float VelocidadFinal(float velInicial, float gravedad, float tiempo);
float VelocidadFinal(float velInicial, float gravedad);

}


#endif
