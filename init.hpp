#ifndef _INIT_HPP_
#define _INIT_HPP_

#include "objloader.hpp"
#include "camara.hpp"
#include "angulo.hpp"
#include "indicePlano.hpp"
#include "textura.hpp"
#include "skybox.hpp"

using namespace std;
using namespace ed;

//extern int largo, alto;

class InitVentana
{
private:
	float _height;
	float _width;
	float _x;
	float _y;
	bool _fullscreen;
public:
	InitVentana(float height = 800, float width = 600, float x = 100, float y = 100, bool fullscreen = false)
	{
		_height = height;
		_width = width;
		_x = x;
		_y = y;
		_fullscreen = fullscreen;
	}

	inline float getHeight() const
	{
		return _height;
	}
	inline float getWidth() const
	{
		return _width;
	}
	inline float getX() const
	{
		return _x;
	}
	inline float getY() const
	{
		return _y;
	}
	inline bool getFullscreen() const
	{
		return _fullscreen;
	}

	void initVentana();
};

vector<vector3d> Rotar(vector<vector3d> modelo, vector3d orientacion, float angulo);
vector<vector3d> Escalar(vector<vector3d> modelo, vector3d escala);
vector<vector3d> Trasladar(vector<vector3d> modelo, vector3d nuevasCoordenadas);

#endif
