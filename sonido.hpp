#ifndef _SONIDO_HPP_
#define _SONIDO_HPP_

#include <AL/alut.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "vector3d.hpp"

using namespace std;
using namespace ed;
using std::string;

class Sonido
{
private:
	ALuint _buffer;
	ALuint _source;
	string _fichero;
	vector3d _PosicionSource;
	vector3d _VelocidadSource;
	bool _loop;
public:
	Sonido()
	{
		_loop = false;
	}
	Sonido(string fichero, vector3d PosicionSource = vector3d(0, 0, 0), vector3d VelocidadSource = vector3d(0, 0, 0), bool loop = false)
	{
		_fichero = fichero;
		_PosicionSource = PosicionSource;
		_VelocidadSource = VelocidadSource;
		_loop = loop;
	}

	inline ALuint getBuffer() const
	{
		return _buffer;
	}
	inline ALuint getSource() const
	{
		return _source;
	}
	inline string getFichero() const
	{
		return _fichero;
	}
	inline vector3d getPosicionSource() const
	{
		return _PosicionSource;
	}
	inline vector3d getVelocidadSource() const
	{
		return _VelocidadSource;
	}
	inline bool getLoop() const
	{
		return _loop;
	}

	inline void setBuffer(ALuint buffer)
	{
		_buffer = buffer;
	}
	inline void setSource(ALuint source)
	{
		_source = source;
	}
	inline void setFichero(string fichero)
	{
		_fichero = fichero;
	}
	inline void setPosicionSource(vector3d PosicionSource)
	{
		_PosicionSource = PosicionSource;
	}
	inline void setVelocidadSource(vector3d VelocidadSource)
	{
		_VelocidadSource = VelocidadSource;
	}
	inline void setLoop(bool loop)
	{
		_loop = loop;
	}

void actualizarSonido(vector3d posicion);
void actualizarSonido();
void definirSonidoSinDoppler();
void terminarSonido();
void leerFichero();
void reproducirSonido();
void pararSonido();
};

void initSonido(int argc, char **argv);
void listener(vector3d posicion);


#endif
