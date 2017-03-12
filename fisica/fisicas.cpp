#include "fisicas.hpp"

using namespace std;
using namespace ed;

namespace ed{

void Particula::Actualizar()
{
	
}

//Formula de la gravedad, devlverá la fuerza en Newtons
float gravedad(vector3d posicion1, vector3d posicion2, float masa1, float masa2, float constanteGravedad)
{
	float distancia = modulo(posicion2 - posicion1);
	return constanteGravedad * masa1 * masa2 / (distancia * distancia);
}

//Formula de la segunda ley de Newton en el que se obtiene la aceleracion mediante la fuerza en Newtons relacionada con la masa del objeto 2
float velocidadAceleracion(float fuerza, float masa)
{
	return fuerza/masa;
}

float CapturaFrames()
{
	static int last = glutGet(GLUT_ELAPSED_TIME);
	int cur = glutGet(GLUT_ELAPSED_TIME);
	float dt = (cur - last)/1000.0;
	last = cur;
	return dt;
}

float CaidaLibre(float tiempo, float velInicial, float gravedad, float posInicial)
{
	//float y = -0.5f*gravedad*(tiempo*tiempo) + velInicial*tiempo + posInicial;
	float y = -0.5f*gravedad*(tiempo*tiempo) + velInicial*tiempo;// + posInicial;
	return y;
}

float VelocidadFinal(float velInicial, float gravedad, float tiempo)
{
	return velInicial + gravedad*tiempo;
}

float VelocidadFinal(float velInicial, float gravedad)
{
	float frames = CapturaFrames();
	return velInicial + gravedad*frames;
}

/*
void parabola(vector3d posicion, vector3d objetivo, float grados, )
{
	vector3d distancia = objetivo - posicion;
	float distObjetivo = sqrt(distancia.getX()*distancia.getX() + distancia.getZ()*distancia.getZ());
	distancia.normalizarVector();
	
}
*/

/*
void parabola()
{
	
}
*/

}
