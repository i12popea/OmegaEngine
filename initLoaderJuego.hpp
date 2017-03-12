#ifndef _INITLOADERJUEGO_HPP_
#define _INITLOADERJUEGO_HPP_

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <ctype.h>
#include "shader.hpp"
#include "vector3d.hpp"
#include "camara.hpp"
#include "angulo.hpp"
#include "indicePlano.hpp"
#include "textura.hpp"
#include "jugador.hpp"
#include "init.hpp"
#include "objloader.hpp"
#include "md5modelo.hpp"
#include "FSM.hpp"
#include "enemigo.hpp"
#include "procedural.hpp"
#include "item.hpp"
#include "sonido.hpp"
#include "skybox.hpp"
#include "Frustum.hpp"
#include "iluminacion.hpp"
#include "fisica/colision.hpp"
#include "fisica/fisicas.hpp"
#include "fisica/colisionEsfera.hpp"
#include "fisica/octree.hpp"

using namespace std;
using namespace ed;
using std::vector;

namespace ed{

class ConfiguracionJuego
{
private:
	static ConfiguracionJuego *_instancia;
	InitVentana _ventana;
	Jugador _jugador;
	Frustum _frustum;
	vector<string> _modelo;
	vector<Objeto> _objeto;
	vector<md5_model_t> _modeloMD5;
	vector<TipoObjeto> _tipoObjeto;
	vector<int> _indiceObjetos;
	vector<string> _tipoColision;
	vector<vector3d> _posicion;
	vector<float> _grados;
	vector<vector3d> _rotacion;
	vector<vector3d> _escalado;
	vector< vector<vector3d> > _objetoColision;
	vector<Box> _colisionBox;
	vector<Esfera> _colisionSphere;
	vector<Octree*> _colisionOctree;
	vector<string> _textura;
	vector<vector3d> _areaCesped;
	vector<vector3d> _cesped;
	vector<vector3d> _colorCesped;
	vector<Enemigo> _enemigos;
	bool _existeCielo;
	vector<string> _parteCielo;
	vector<int> _cielo;
	float _tamanoSkybox;
	vector3d _posicionCielo;
	vector<Sonido> _sonidos;
	vector<string> _nombreSonido;
	vector<vector3d> _posicionSonido;
//	vector<Iluminacion> _luces;
	ListaIluminacion _luces;
	vector<Shader> _shader;
public:
	static ConfiguracionJuego* Instancia()
	{
		if (!_instancia)
			_instancia = new ConfiguracionJuego;
		return _instancia;
	}

	//Modificadores
	inline void setExisteCielo(bool valor)
	{
		_existeCielo=valor;
	}

	//Observadores
	inline InitVentana getVentana() const
	{
		return _ventana;
	}
	inline Jugador *getJugador()
	{
		return &_jugador;
	}
	inline string getModelo(int indice)
	{
		return _modelo[indice];
	}
	inline Objeto getObjeto(int indice)
	{
		return _objeto[indice];
	}
	inline vector3d getPosicion(int indice)
	{
		return _posicion[indice];
	}
	inline string getTextura(int indice)
	{
		return _textura[indice];
	}
	inline bool getExisteCielo() const
	{
		return _existeCielo;
	}
	inline string getParteCielo(int indice) const
	{
		return _parteCielo[indice];
	}
	inline int getCielo(int indice) const
	{
		return _cielo[indice];
	}
	inline string getNombreSonido(int indice)
	{
		return _nombreSonido[indice];
	}
	inline vector3d getPosicionSonido(int indice)
	{
		return _posicionSonido[indice];
	}

	//Metodos
	void CargaConfiguracion(string fichero);
	void IniciarFramework(int argc, char *argv[]);
	void contadorFPS();
	void dibujarContadorFPS();
	void dibujarHUD();

	void display();
	static void displayCallBack();

	void redibujar();
	static void redibujarCallBack();

	void reshape(int w, int h);
	static void reshapeCallBack(int w, int h);

	void keyboard(unsigned char key, int x, int y);
	static void keyboardCallBack(unsigned char key, int x, int y);

	void keyboardUp(unsigned char key, int x, int y);
	static void keyboardUpCallBack(unsigned char key, int x, int y);

	void movimiento(int x, int y);
	static void movimientoCallBack(int x, int y);

	void raton(int boton, int estado, int x, int y);
	static void ratonCallBack(int boton, int estado, int x, int y);

	void movimientoJugador();
	void initMouse();
	void init();
	void enable();
	void ReorganizarModelos();
//	void PrepararShader(int textura);
};
vector<string> CadenaAString(string cadena, string delimitador);
int NumeroElementos(string cadena);

}

#endif
