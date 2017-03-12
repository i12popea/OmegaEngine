#ifndef _ENEMIGO_HPP_
#define _ENEMIGO_HPP_

#include <cstdlib>
#include <time.h>
#include "objloader.hpp"
#include "camara.hpp"
//#include "arma.hpp"
#include "FSM.hpp"
#include "fisica/colisionCubo.hpp"
#include "fisica/colision.hpp"
#include "fisica/fisicas.hpp"

using namespace std;

namespace ed
{

class Enemigo
{
private:
	FSM _brain;
	bool _activo;
	bool _muerto;
	bool _caer;
	bool _colision;
	bool _nearcollision;
	Camara _camara;
	vector3d _posicion;
	Angulo _angulo;
	vector3d _PosicionJugador;
//	float _posicionInicial;
//	Arma _arma;
	int _salud;
//	int _armadura;
//	float _velocidadJugador;
//	bool _salto;
//	bool _agachado;
//	Sonido _sonidoSalto;
	Cilindro _bounding;
//	Cilindro _boundingDePie;
//	Cilindro _boundingAgachado;
//	float _tiempo;
//	float _impulsoInicial; // Si es 0 no hay impulso para subir; solo para bajar, si es 13 hay impulso para realizar el salto
//	float _antesDeColision;
//	float _despuesDeColision;
public:
	//Constructor
	Enemigo(Estado estado = CAMINAR)
	{
		_brain.setEstado(estado);
		_activo = false;
		_muerto = false;
		_caer = false;
		_colision = false;
		_nearcollision = false;
		_camara = Camara(0, 4, 0); //Mirar luego
		_posicion = vector3d(0, 0, 0);
	//	_posicionInicial = (13*13)/(2*9.8);
		_salud = 100;
	//	_armadura = 0;
	//	_velocidadJugador = 0.25f;
	//	_salto = false;
	//	_agachado = false;
		//_tiempo = 0.0;
	//	_impulsoInicial = 0.0;
		_bounding = Cilindro(vector3d(0, 2, 0), 2, 1);
	//	_boundingDePie = Cilindro(vector3d(0, 2, 0), 2, 1);
	//	_boundingAgachado = Cilindro(vector3d(0, 1, 0), 1, 1);
	//	_antesDeColision = _camara.getVector().getY() - _bounding.getAltura();
	}

	Enemigo(vector3d posicion, Estado estado = CAMINAR, int salud = 0, int armadura = 0)
	{
		_brain.setEstado(estado);
		_activo = false;
		_muerto = false;
		_caer = false;
		_colision = false;
		_nearcollision = false;
		_posicion = posicion;
		_camara.setVector(posicion.getX(), posicion.getY() + 4, posicion.getZ());
	//	_posicionInicial = (13*13)/(2*9.8);
		_salud = salud;
		//_armadura = armadura;
	//	_velocidadJugador = 0.25;
	//	_salto = false;
	//	_agachado = false;
		//_tiempo = 0.0;
	//	_impulsoInicial = 0.0;
		_bounding = Cilindro(vector3d(posicion.getX(), posicion.getY(), posicion.getZ()), 2, 1);
	//	_boundingDePie = Cilindro(vector3d(posicion.getX(), posicion.getY(), posicion.getZ()), 2, 1);
	//	_boundingAgachado = Cilindro(vector3d(posicion.getX(), posicion.getY(), posicion.getZ()), 1, 1);
	//	_antesDeColision = _camara.getVector().getY() - _bounding.getAltura();
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

	/*inline Arma* getArma()
	{
		return &_arma;
	}*/

	inline int getSalud() const
	{
		return _salud;
	}

	/*inline int getArmadura() const
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
	}*/

	inline Cilindro* getBounding()
	{
		return &_bounding;
	}

	/*inline float getAntes() const
	{
		return _antesDeColision;
	}*/

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

	/*inline void setArmadura(int armadura)
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
	}*/

	void SaludDanada(int cantidad);

	void Caminar();
	void Muerto();
	void Perseguir();
	void CambiarDir();
	void Activo();
	void Esquivar();
	void Atacar();
	void Avanzar();
	void ColisionEnemigo(vector<Box> boxes, vector<Esfera> esferas, vector<Octree*> objetoOctree);
	void ActualizarEstado();
	/*void MostrarArma();
	//void SaludRegenerada();
	void ActualizarPosicion();
	void ColisionPersonaje(vector<Box> &boxes, vector<Esfera> &esferas, vector<Octree*> &objetoOctree, vector<TipoObjeto> &tipoObjeto, vector<Objeto> &objetos, vector<vector3d> &posicion, vector<float> &grados, vector<vector3d> &rotacion, vector<vector3d> &escalado);
	void Salto();
	void Agacharse();
	void ObtenerAngulos();*/
};

}

#endif
