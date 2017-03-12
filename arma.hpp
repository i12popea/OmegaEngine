#ifndef _ARMA_HPP_
#define _ARMA_HPP_

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "vector3d.hpp"
#include "sonido.hpp"
#include <GL/glut.h>

using namespace std;
using std::vector;

namespace ed{

class Municion
{
private:
	vector3d _posicion;
	vector3d _objetivo;
	vector3d _salida;
	float _xrot;
	float _yrot;
public:
	inline vector3d getPosicion()
	{
		return _posicion;
	}
	inline vector3d getObjetivo()
	{
		return _objetivo;
	}
	inline float getXrot()
	{
		return _xrot;
	}
	inline float getYrot()
	{
		return _yrot;
	}
	inline vector3d getSalida()
	{
		return _salida;
	}

	inline void setPosicion(vector3d posicion)
	{
		_posicion = posicion;
	}
	inline void setObjetivo(vector3d objetivo)
	{
		_objetivo = objetivo;
	}
	inline void setXrot(float xrot)
	{
		_xrot = xrot;
	}
	inline void setYrot(float yrot)
	{
		_yrot = yrot;
	}
	inline void setSalida(vector3d salida)
	{
		_salida = salida;
	}
};

class Arma
{
private:
	int _municion;
	bool _EsDisparado;
	bool _EsAutomatico; //Esto hace que se siga disparando altener presionado el botón izquierdo del raton, sino sería manual
	int _dano;
	vector3d _posicion;
	vector3d _objetivo;
	vector3d _salida;
	float _xrot;
	float _yrot;
	vector<Municion> _municionDisparada;
	Sonido _sonido;
public:
	Arma(float municion = 30, bool EsDisparado = false, bool EsAutomatico = false, float dano = 10)
	{
		setMunicion(municion);
		setDisparado(EsDisparado);
		setAutomatico(EsAutomatico);
		setDano(dano);
		_municionDisparada.resize(0);
	};
	~Arma(){};

	//Observadores
	inline float getMunicion() const
	{
		return _municion;
	}
	inline bool getDisparado() const
	{
		return _EsDisparado;
	}
	inline bool getAutomatico() const
	{
		return _EsAutomatico;
	}
	inline float getDano() const
	{
		return _dano;
	}
	inline vector3d getPosicion() const
	{
		return _posicion;
	}
	inline vector3d getObjetivo() const
	{
		return _objetivo;
	}
	inline vector<Municion>* getMunicionDisparada()
	{
		return &_municionDisparada;
	}
	inline Municion getMunicionDisparada(int indice)
	{
		return _municionDisparada[indice];
	}
	inline Sonido getSonido() const
	{
		return _sonido;
	}

	//Modificadores
	inline void setMunicion(int municion)
	{
		_municion = municion;
	}
	inline void setDisparado(bool EsDisparado)
	{
		_EsDisparado = EsDisparado;
	}
	inline void setAutomatico(bool EsAutomatico)
	{
		_EsAutomatico = EsAutomatico;
	}
	inline void setDano(float dano)
	{
		_dano = dano;
	}
	inline void setPosicion(vector3d posicion)
	{
		_posicion.setX(posicion.getX());
		_posicion.setY(posicion.getY());
		_posicion.setZ(posicion.getZ());
	}
	inline void setObjetivo(vector3d objetivo)
	{
		_objetivo.setX(objetivo.getX());
		_objetivo.setY(objetivo.getY());
		_objetivo.setZ(objetivo.getZ());
	}
	
void DibujarArma();
void DibujarProyectil(vector3d posicion, vector3d objetivo, float xrot, float yrot);
void Disparo();
void AumentarMunicion();
	
};

}

#endif
