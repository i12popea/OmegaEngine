#ifndef _FRUSTUM_HPP_
#define _FRUSTUM_HPP_

#include "vector3d.hpp"
#include "fisica/colisionCubo.hpp"
#include "fisica/colisionEsfera.hpp"
#include <vector>

using namespace std;
using std::vector;

namespace ed{

class Frustum
{
public:
	float _frustum[6][4];

	void ExtraerFrustum();
	bool CubeInFrustum( vector3d centro, float alto, float largo, float ancho );
	int CubeInFrustum2( vector3d centro, float alto, float largo, float ancho );
	bool sphereInFrustum(Esfera esfera/*vector3d centro, float radio*/);
	bool PointInFrustum(vector3d punto);
};

}

#endif
