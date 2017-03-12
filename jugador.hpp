#ifndef _JUGADOR_HPP_
#define _JUGADOR_HPP_

#include <cstdlib>
#include <time.h>
#include "objloader.hpp"
#include "camara.hpp"
#include "arma.hpp"
#include "fisica/colisionCubo.hpp"
#include "fisica/colision.hpp"
#include "fisica/fisicas.hpp"

using namespace std;

namespace ed
{

class Jugador
{
private:
	Camara _camara;
	vector3d _posicion;
	float _posicionInicial;
	Arma _arma;
	int _salud;
	int _armadura;
	float _velocidadJugador;
	bool _salto;
	bool _agachado;
	Sonido _sonidoSalto;
	Cilindro _bounding;
	Cilindro _boundingDePie;
	Cilindro _boundingAgachado;
	float _tiempo;
	float _impulsoInicial; // Si es 0 no hay impulso para subir; solo para bajar, si es 13 hay impulso para realizar el salto
	float _antesDeColision;
	float _despuesDeColision;
public:
	//Constructor
	Jugador()
	{
		_camara = Camara(0, 4, 0); //Mirar luego
		_posicion = vector3d(0, 0, 0);
		_posicionInicial = (13*13)/(2*9.8);
		_salud = 100;
		_armadura = 0;
		_velocidadJugador = 0.25f;
		_salto = false;
		_agachado = false;
		_tiempo = 0.0;
		_impulsoInicial = 0.0;
		_bounding = Cilindro(vector3d(0, 2, 0), 2, 1);
		_boundingDePie = Cilindro(vector3d(0, 2, 0), 2, 1);
		_boundingAgachado = Cilindro(vector3d(0, 1, 0), 1, 1);
		_antesDeColision = _camara.getVector().getY() - _bounding.getAltura();
	}

	Jugador(Camara camara, /*vector3d posicion, */int salud = 100, int armadura = 0)
	{
		//_posicion = posicion;
		//_camara.setVector(posicion.getX(), posicion.getY() + 4, posicion.getZ());
		_camara.setVector(camara.getVector().getX(), camara.getVector().getY(), camara.getVector().getZ());
		_posicionInicial = (13*13)/(2*9.8);
		_salud = salud;
		_armadura = armadura;
		_velocidadJugador = 0.25;
		_salto = false;
		_agachado = false;
		_tiempo = 0.0;
		_impulsoInicial = 0.0;
		/*_bounding = Cilindro(vector3d(posicion.getX(), posicion.getY(), posicion.getZ()), 2, 1);
		_boundingDePie = Cilindro(vector3d(posicion.getX(), posicion.getY(), posicion.getZ()), 2, 1);
		_boundingAgachado = Cilindro(vector3d(posicion.getX(), posicion.getY(), posicion.getZ()), 1, 1);*/
		_bounding = Cilindro(vector3d(camara.getVector().getX(), camara.getVector().getY() - 2, camara.getVector().getZ()), 2, 1);
		_boundingDePie = Cilindro(vector3d(camara.getVector().getX(), camara.getVector().getY() - 2, camara.getVector().getZ()), 2, 1);
		_boundingAgachado = Cilindro(vector3d(camara.getVector().getX(), camara.getVector().getY() - 3, camara.getVector().getZ()), 1, 1);
		_antesDeColision = _camara.getVector().getY() - _bounding.getAltura();
	}

	inline Camara* getCamara()
	{
		return &_camara;
	}
	inline Camara getCam()
	{
		return _camara;
	}

	inline vector3d getVector3d() const
	{
		return _posicion;
	}

	inline Arma* getArma()
	{
		return &_arma;
	}

	inline int getSalud() const
	{
		return _salud;
	}

	inline int getArmadura() const
	{
		return _armadura;
	}

	inline float getVelocidadJugador() const
	{
		return _velocidadJugador;
	}

	inline bool getSalto() const
	{
		return _salto;
	}

	inline bool getAgachado() const
	{
		return _agachado;
	}

	inline float getImpulsoInicial() const
	{
		return _impulsoInicial;
	}

	inline Cilindro* getBounding()
	{
		return &_bounding;
	}

	inline float getAntes() const
	{
		return _antesDeColision;
	}

	inline void setVector3d(vector3d vector)
	{
		_posicion.setX(vector.getX());
		_posicion.setY(vector.getY());
		_posicion.setZ(vector.getZ());
	}

	/*inline void setArma(Arma arma) //Mirar luego
	{
		_arma = arma;
	}*/

	inline void setSalud(int salud)
	{
		_salud = salud;
	}

	inline void setArmadura(int armadura)
	{
		_armadura = armadura;
	}

	inline void setVelocidadJugador(float velocidad)
	{
		_velocidadJugador = velocidad;
	}

	inline void setSalto(bool salto)
	{
		_salto = salto;
	}

	inline void setAgachado(bool agachado)
	{
		_agachado = agachado;
	}

	inline void setImpulsoInicial(float impulsoInicial)
	{
		_impulsoInicial = impulsoInicial;
	}

	Jugador & operator = (Jugador const &jugador);

	void MostrarArma();
	void SaludDanada(int cantidad);
	void SaludRegenerada();
	void ActualizarPosicion();
	void ColisionPersonaje(vector<Box> &boxes, vector<Esfera> &esferas, vector<Octree*> &objetoOctree, vector<TipoObjeto> &tipoObjeto, vector<Objeto> &objetos, vector<vector3d> &posicion, vector<float> &grados, vector<vector3d> &rotacion, vector<vector3d> &escalado);
	void Salto();
	void Agacharse();
	void ObtenerAngulos();
};

}

#endif
