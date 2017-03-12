#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "textura.hpp"
#include "vector3d.hpp"
#include <vector>
#include <GL/glut.h>

using namespace std;
using namespace ed;
using std::vector;

class Menu{
private:
	int _background;
	vector<vector2d> _coordBackground;
	vector<vector3d> _posBackground;
	vector3d _colorBackground;
	vector<int> _botones;
	vector<vector2d> _coordBoton1;
	vector<vector3d> _posBoton1;
	vector3d _colorBoton1;
	vector<vector2d> _coordBoton2;
	vector<vector3d> _posBoton2;
	vector3d _colorBoton2;
	vector<vector2d> _coordBoton3;
	vector<vector3d> _posBoton3;
	vector3d _colorBoton3;
public:
	inline void setBackground(int background)
	{
		_background = background;
	}
	inline void setCoordBackground(vector<vector2d> coordBackground)
	{
		_coordBackground = coordBackground;
	}
	inline void setPosBackground(vector<vector3d> posBackground)
	{
		_posBackground = posBackground;
	}
	inline void setColorBackground(vector3d colorBackground)
	{
		_colorBackground = colorBackground;
	}

	inline void setCoordBoton1(vector<vector2d> coordBoton1)
	{
		_coordBoton1 = coordBoton1;
	}
	inline void setPosBoton1(vector<vector3d> posBoton1)
	{
		_posBoton1 = posBoton1;
	}
	inline void setColorBoton1(vector3d colorBoton1)
	{
		_colorBoton1 = colorBoton1;
	}
	inline void setCoordBoton2(vector<vector2d> coordBoton2)
	{
		_coordBoton2 = coordBoton2;
	}
	inline void setPosBoton2(vector<vector3d> posBoton2)
	{
		_posBoton2 = posBoton2;
	}
	inline void setColorBoton2(vector3d colorBoton2)
	{
		_colorBoton2 = colorBoton2;
	}
	inline void setCoordBoton3(vector<vector2d> coordBoton3)
	{
		_coordBoton3 = coordBoton3;
	}
	inline void setPosBoton3(vector<vector3d> posBoton3)
	{
		_posBoton3 = posBoton3;
	}
	inline void setColorBoton3(vector3d colorBoton3)
	{
		_colorBoton3 = colorBoton3;
	}

	inline vector3d getColorBackground()
	{
		return _colorBackground;
	}
	inline vector<vector3d> getPosBoton1()
	{
		return _posBoton1;
	}
	inline vector<vector3d> getPosBoton2()
	{
		return _posBoton2;
	}
	inline vector<vector3d> getPosBoton3()
	{
		return _posBoton3;
	}

void IniciarMenu();
void MostrarMenu();
};

bool AABBPoint(vector3d esquina1, vector3d esquina2, vector2d punto);

#endif
