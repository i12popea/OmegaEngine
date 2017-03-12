#include "sonido.hpp"

using namespace std;
using namespace ed;

void initSonido(int argc, char **argv)
{
	alutInit(&argc, argv);
}

void listener(vector3d posicion)
{
	ALfloat listenerPos[3];
	listenerPos[0] = posicion.getX();
	listenerPos[1] = posicion.getY();
	listenerPos[2] = posicion.getZ();

	ALfloat listenerVel[] = {0.0,0.0,0.0};
	ALfloat listenerOri[] = {0.0,0.0,1.0, 0.0,1.0,0.0};

	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
}

void Sonido::actualizarSonido(vector3d posicion)
{
	ALfloat listenerPos[3];
	listenerPos[0] = posicion.getX();
	listenerPos[1] = posicion.getY();
	listenerPos[2] = posicion.getZ();

	ALfloat sourceDir[3];
	sourceDir[0] = _PosicionSource.getX();
	sourceDir[1] = _PosicionSource.getY();
	sourceDir[2] = _PosicionSource.getZ();

	ALfloat listenerVel[3];
	listenerVel[0] = _VelocidadSource.getX();
	listenerVel[1] = _VelocidadSource.getY();
	listenerVel[2] = _VelocidadSource.getZ();

	alSourcef(_source, AL_PITCH, 1.0f);
	alSourcef(_source, AL_GAIN, 1.0f);

	alListenerfv(AL_VELOCITY, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_DIRECTION, sourceDir);

	if(_loop)
		alSourcei(_source, AL_LOOPING, AL_TRUE);
}

void Sonido::actualizarSonido()
{
	ALfloat sourcePos[3];
	sourcePos[0] = _PosicionSource.getX();
	sourcePos[1] = _PosicionSource.getY();
	sourcePos[2] = _PosicionSource.getZ();

	ALfloat sourceVel[3];
	sourceVel[0] = _VelocidadSource.getX();
	sourceVel[1] = _VelocidadSource.getY();
	sourceVel[2] = _VelocidadSource.getZ();

	alSourcef(_source, AL_PITCH, 1.0f);
	alSourcef(_source, AL_GAIN, 1.0f);

	alListenerfv(AL_POSITION, sourcePos);
	alListenerfv(AL_VELOCITY, sourceVel);
	alSourcei(_source, AL_BUFFER, _buffer);

	if(_loop)
		alSourcei(_source, AL_LOOPING, AL_TRUE);
}

void Sonido::definirSonidoSinDoppler()
{
	alSourcei(_source, AL_BUFFER, _buffer);

	if(_loop)
		alSourcei(_source, AL_LOOPING, AL_TRUE);
}

void Sonido::terminarSonido()
{
	alutExit();
}

void Sonido::leerFichero()
{
	_buffer = alutCreateBufferFromFile(_fichero.c_str());
	alGenSources(1, &_source);
	alSourcei(_source, AL_BUFFER, _buffer);
}

void Sonido::reproducirSonido()
{
	alSourcePlay(_source);
}

void Sonido::pararSonido()
{
	alSourceStop(_source);
}
