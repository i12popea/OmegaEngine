#include "init.hpp"

using namespace std;
using namespace ed;

void InitVentana::initVentana()
{
	ifstream config("config.conf", ios::in);
	if(!config)
	{
		cerr << "Error al leer el archivo de configuracion de ventana\n";
		exit(1);
	}

	string linea;
	while(getline(config, linea))
	{
		if(linea.substr(0, 7) == "Height ")
		{
			istringstream s(linea.substr(7));
			float temporal; s >> temporal;
			_height = temporal;
		}
		if(linea.substr(0, 6) == "Width ")
		{
			istringstream s(linea.substr(6));
			float temporal; s >> temporal;
			_width = temporal;
		}
		if(linea.substr(0, 2) == "X ")
		{
			istringstream s(linea.substr(2));
			float temporal; s >> temporal;
			_x = temporal;
		}
		if(linea.substr(0, 2) == "Y ")
		{
			istringstream s(linea.substr(2));
			float temporal; s >> temporal;
			_y = temporal;
		}
		if(linea.substr(0, 11) == "Fullscreen ")
		{
			string full(linea.substr(11));
			if(full == "true")
				_fullscreen = true;
			if(full == "false")
				_fullscreen = false;
		}
	}
	config.close();
}

vector<vector3d> Rotar(vector<vector3d> modelo, vector3d orientacion, float angulo)
{
	vector<vector3d> modeloRotado;
	float XRot, YRot, ZRot;
	float radian = 3.14159265359f/180.0f;
	if(angulo == 0)
		return modelo;
	if((orientacion.getX() == 0) && (orientacion.getY() == 0) && (orientacion.getZ() == 0))
		return modelo;
	if(orientacion.getX() != 0)
	{
		for(unsigned int i = 0; i < modelo.size(); i++)
		{
			XRot = modelo[i].getX();
			YRot = modelo[i].getY()*cos(radian*angulo) - modelo[i].getZ()*sin(radian*angulo);
			ZRot = modelo[i].getY()*sin(radian*angulo) + modelo[i].getZ()*cos(radian*angulo);
			modeloRotado.push_back(vector3d(XRot, YRot, ZRot));
		}
	}
	if(orientacion.getY() != 0)
	{
		for(unsigned int i = 0; i < modelo.size(); i++)
		{
			XRot = modelo[i].getX()*cos(radian*angulo) + modelo[i].getZ()*sin(radian*angulo);
			YRot = modelo[i].getY();
			ZRot = -modelo[i].getX()*sin(radian*angulo) + modelo[i].getZ()*cos(radian*angulo);
			modeloRotado.push_back(vector3d(XRot, YRot, ZRot));
		}
	}
	if(orientacion.getZ() != 0)
	{
		for(unsigned int i = 0; i < modelo.size(); i++)
		{
			XRot = modelo[i].getX()*cos(radian*angulo) - modelo[i].getY()*sin(radian*angulo);
			YRot = modelo[i].getX()*sin(radian*angulo) + modelo[i].getY()*cos(radian*angulo);
			ZRot = modelo[i].getZ();
			modeloRotado.push_back(vector3d(XRot, YRot, ZRot));
		}
	}
	return modeloRotado;
}

vector<vector3d> Escalar(vector<vector3d> modelo, vector3d escala)
{
	vector<vector3d> modeloEscalado;
	for(unsigned int i = 0; i < modelo.size(); i++)
	{
		modeloEscalado.push_back(vector3d(modelo[i].getX() * escala.getX(), modelo[i].getY() * escala.getY(), modelo[i].getZ() * escala.getZ()));
	}
	return modeloEscalado;
}

vector<vector3d> Trasladar(vector<vector3d> modelo, vector3d nuevasCoordenadas)
{
	vector<vector3d> modeloTrasladado;
	for(unsigned int i = 0; i < modelo.size(); i++)
	{
		//modeloTrasladado.push_back(vector3d(modelo[i].getX() + nuevasCoordenadas.getX(), modelo[i].getY() + nuevasCoordenadas.getY(), modelo[i].getZ() + nuevasCoordenadas.getZ()));
		modeloTrasladado.push_back(modelo[i] + nuevasCoordenadas);
	}
	return modeloTrasladado;
}
