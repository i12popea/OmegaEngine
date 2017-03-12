#include "iluminacion.hpp"

using namespace std;
using namespace ed;

namespace ed{

void ListaIluminacion::IniciarIluminacion()
{
	unsigned int i;
	int j, k;
	for(i = 0, j = 0, k = 0; i < _focos.size(); i++, j = j + 3, k = k + 4)
	{
		_LightPosition[j] = _focos[i].getPosicion().getX(); _LightPosition[j + 1] = _focos[i].getPosicion().getY(); _LightPosition[j + 2] = _focos[i].getPosicion().getZ();
		_LightColor[k] = _focos[i].getColor()[0]; _LightColor[k + 1] = _focos[i].getColor()[1]; _LightColor[k + 2] = _focos[i].getColor()[2]; _LightColor[k + 3] = 0;
	}
}

void ListaIluminacion::IluminarEscena()
{
	GLfloat ambiente[4];
	GLfloat difusa[4];
	GLfloat especular[4];
	GLfloat posicion[4];

	if(_focos.size() >= 1)
	{
		ambiente[0] = _focos[0].getAmbiente().getX(); ambiente[1] = _focos[0].getAmbiente().getY(); ambiente[2] = _focos[0].getAmbiente().getZ(); ambiente[3] = 1;
		difusa[0] = _focos[0].getDifusa().getX(); difusa[1] = _focos[0].getDifusa().getY(); difusa[2] = _focos[0].getDifusa().getZ(); difusa[3] = 1;
		especular[0] = _focos[0].getEspecular().getX(); especular[1] = _focos[0].getEspecular().getY(); especular[2] = _focos[0].getEspecular().getZ(); especular[3] = 1;
		posicion[0] = _focos[0].getPosicion().getX(); posicion[1] = _focos[0].getPosicion().getY(); posicion[2] = _focos[0].getPosicion().getZ(); posicion[3] = 0;
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
		glLightfv(GL_LIGHT0, GL_SPECULAR, especular);
		glLightfv(GL_LIGHT0, GL_POSITION, posicion);
	}

	if(_focos.size() >= 2)
	{
		ambiente[0] = _focos[1].getAmbiente().getX(); ambiente[1] = _focos[1].getAmbiente().getY(); ambiente[2] = _focos[1].getAmbiente().getZ(); ambiente[3] = 1;
		difusa[0] = _focos[1].getDifusa().getX(); difusa[1] = _focos[1].getDifusa().getY(); difusa[2] = _focos[1].getDifusa().getZ(); difusa[3] = 1;
		especular[0] = _focos[1].getEspecular().getX(); especular[1] = _focos[1].getEspecular().getY(); especular[2] = _focos[1].getEspecular().getZ(); especular[3] = 1;
		posicion[0] = _focos[1].getPosicion().getX(); posicion[1] = _focos[1].getPosicion().getY(); posicion[2] = _focos[1].getPosicion().getZ(); posicion[3] = 0;
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, difusa);
		glLightfv(GL_LIGHT1, GL_SPECULAR, especular);
		glLightfv(GL_LIGHT1, GL_POSITION, posicion);
	}

	if(_focos.size() >= 3)
	{
		ambiente[0] = _focos[2].getAmbiente().getX(); ambiente[1] = _focos[2].getAmbiente().getY(); ambiente[2] = _focos[2].getAmbiente().getZ(); ambiente[3] = 1;
		difusa[0] = _focos[2].getDifusa().getX(); difusa[1] = _focos[2].getDifusa().getY(); difusa[2] = _focos[2].getDifusa().getZ(); difusa[3] = 1;
		especular[0] = _focos[2].getEspecular().getX(); especular[1] = _focos[2].getEspecular().getY(); especular[2] = _focos[2].getEspecular().getZ(); especular[3] = 1;
		posicion[0] = _focos[2].getPosicion().getX(); posicion[1] = _focos[2].getPosicion().getY(); posicion[2] = _focos[2].getPosicion().getZ(); posicion[3] = 0;
		glEnable(GL_LIGHT2);
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambiente);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, difusa);
		glLightfv(GL_LIGHT2, GL_SPECULAR, especular);
		glLightfv(GL_LIGHT2, GL_POSITION, posicion);
	}

	if(_focos.size() >= 4)
	{
		ambiente[0] = _focos[3].getAmbiente().getX(); ambiente[1] = _focos[3].getAmbiente().getY(); ambiente[2] = _focos[3].getAmbiente().getZ(); ambiente[3] = 1;
		difusa[0] = _focos[3].getDifusa().getX(); difusa[1] = _focos[3].getDifusa().getY(); difusa[2] = _focos[3].getDifusa().getZ(); difusa[3] = 1;
		especular[0] = _focos[3].getEspecular().getX(); especular[1] = _focos[3].getEspecular().getY(); especular[2] = _focos[3].getEspecular().getZ(); especular[3] = 1;
		posicion[0] = _focos[3].getPosicion().getX(); posicion[1] = _focos[3].getPosicion().getY(); posicion[2] = _focos[3].getPosicion().getZ(); posicion[3] = 0;
		glEnable(GL_LIGHT3);
		glLightfv(GL_LIGHT3, GL_AMBIENT, ambiente);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, difusa);
		glLightfv(GL_LIGHT3, GL_SPECULAR, especular);
		glLightfv(GL_LIGHT3, GL_POSITION, posicion);
	}

	if(_focos.size() >= 5)
	{
		ambiente[0] = _focos[4].getAmbiente().getX(); ambiente[1] = _focos[4].getAmbiente().getY(); ambiente[2] = _focos[4].getAmbiente().getZ(); ambiente[3] = 1;
		difusa[0] = _focos[4].getDifusa().getX(); difusa[1] = _focos[4].getDifusa().getY(); difusa[2] = _focos[4].getDifusa().getZ(); difusa[3] = 1;
		especular[0] = _focos[4].getEspecular().getX(); especular[1] = _focos[4].getEspecular().getY(); especular[2] = _focos[4].getEspecular().getZ(); especular[3] = 1;
		posicion[0] = _focos[4].getPosicion().getX(); posicion[1] = _focos[4].getPosicion().getY(); posicion[2] = _focos[4].getPosicion().getZ(); posicion[3] = 0;
		glEnable(GL_LIGHT4);
		glLightfv(GL_LIGHT4, GL_AMBIENT, ambiente);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, difusa);
		glLightfv(GL_LIGHT4, GL_SPECULAR, especular);
		glLightfv(GL_LIGHT4, GL_POSITION, posicion);
	}

	if(_focos.size() >= 6)
	{
		ambiente[0] = _focos[5].getAmbiente().getX(); ambiente[1] = _focos[5].getAmbiente().getY(); ambiente[2] = _focos[5].getAmbiente().getZ(); ambiente[3] = 1;
		difusa[0] = _focos[5].getDifusa().getX(); difusa[1] = _focos[5].getDifusa().getY(); difusa[2] = _focos[5].getDifusa().getZ(); difusa[3] = 1;
		especular[0] = _focos[5].getEspecular().getX(); especular[1] = _focos[5].getEspecular().getY(); especular[2] = _focos[5].getEspecular().getZ(); especular[3] = 1;
		posicion[0] = _focos[5].getPosicion().getX(); posicion[1] = _focos[5].getPosicion().getY(); posicion[2] = _focos[5].getPosicion().getZ(); posicion[3] = 0;
		glEnable(GL_LIGHT5);
		glLightfv(GL_LIGHT5, GL_AMBIENT, ambiente);
		glLightfv(GL_LIGHT5, GL_DIFFUSE, difusa);
		glLightfv(GL_LIGHT5, GL_SPECULAR, especular);
		glLightfv(GL_LIGHT5, GL_POSITION, posicion);
	}

	if(_focos.size() >= 7)
	{
		ambiente[0] = _focos[6].getAmbiente().getX(); ambiente[1] = _focos[6].getAmbiente().getY(); ambiente[2] = _focos[6].getAmbiente().getZ(); ambiente[3] = 1;
		difusa[0] = _focos[6].getDifusa().getX(); difusa[1] = _focos[6].getDifusa().getY(); difusa[2] = _focos[6].getDifusa().getZ(); difusa[3] = 1;
		especular[0] = _focos[6].getEspecular().getX(); especular[1] = _focos[6].getEspecular().getY(); especular[2] = _focos[6].getEspecular().getZ(); especular[3] = 1;
		posicion[0] = _focos[6].getPosicion().getX(); posicion[1] = _focos[6].getPosicion().getY(); posicion[2] = _focos[6].getPosicion().getZ(); posicion[3] = 0;
		glEnable(GL_LIGHT6);
		glLightfv(GL_LIGHT6, GL_AMBIENT, ambiente);
		glLightfv(GL_LIGHT6, GL_DIFFUSE, difusa);
		glLightfv(GL_LIGHT6, GL_SPECULAR, especular);
		glLightfv(GL_LIGHT6, GL_POSITION, posicion);
	}

	if(_focos.size() == 8)
	{
		ambiente[0] = _focos[7].getAmbiente().getX(); ambiente[1] = _focos[7].getAmbiente().getY(); ambiente[2] = _focos[7].getAmbiente().getZ(); ambiente[3] = 1;
		difusa[0] = _focos[7].getDifusa().getX(); difusa[1] = _focos[7].getDifusa().getY(); difusa[2] = _focos[7].getDifusa().getZ(); difusa[3] = 1;
		especular[0] = _focos[7].getEspecular().getX(); especular[1] = _focos[7].getEspecular().getY(); especular[2] = _focos[7].getEspecular().getZ(); especular[3] = 1;
		posicion[0] = _focos[7].getPosicion().getX(); posicion[1] = _focos[7].getPosicion().getY(); posicion[2] = _focos[7].getPosicion().getZ(); posicion[3] = 0;
		glEnable(GL_LIGHT7);
		glLightfv(GL_LIGHT7, GL_AMBIENT, ambiente);
		glLightfv(GL_LIGHT7, GL_DIFFUSE, difusa);
		glLightfv(GL_LIGHT7, GL_SPECULAR, especular);
		glLightfv(GL_LIGHT7, GL_POSITION, posicion);
	}
}

void ListaIluminacion::InsertarFoco(Iluminacion foco)
{
	if(_focos.size() <= 7)
		_focos.push_back(foco);
}

}
