#include "Frustum.hpp"
#include <cmath>
#include <GL/glut.h>

#define ANG2RAD 3.14159265358979323846/180.0

using namespace std;
using namespace ed;

namespace ed{

void Frustum::ExtraerFrustum()
{
	float proj[16];
	float modl[16];
	float clip[16];
	float t;

	/* Get the current PROJECTION matrix from OpenGL */
	glGetFloatv( GL_PROJECTION_MATRIX, proj );

	/* Get the current MODELVIEW matrix from OpenGL */
	glGetFloatv( GL_MODELVIEW_MATRIX, modl );

	/* Combine the two matrices (multiply projection by modelview)    */
	clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] +    modl[ 3] * proj[12];
	clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] +    modl[ 3] * proj[13];
	clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] +    modl[ 3] * proj[14];
	clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] +    modl[ 3] * proj[15];

	clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4]    + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
	clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] +    modl[ 7] * proj[13];
	clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] +    modl[ 7] * proj[14];
	clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] +    modl[ 7] * proj[15];

	clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4]    + modl[10] * proj[ 8] + modl[11] * proj[12];
	clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] +    modl[11] * proj[13];
	clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] +    modl[11] * proj[14];
	clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] +    modl[11] * proj[15];

	clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4]    + modl[14] * proj[ 8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] +    modl[15] * proj[13];
	clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] +    modl[15] * proj[14];
	clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] +    modl[15] * proj[15];

	/* Extract the numbers for the RIGHT plane */
	_frustum[0][0] = clip[ 3] - clip[ 0];
	_frustum[0][1] = clip[ 7] - clip[ 4];
	_frustum[0][2] = clip[11] - clip[ 8];
	_frustum[0][3] = clip[15] - clip[12];

	/* Normalize the result */
	t = sqrt( _frustum[0][0] * _frustum[0][0] + _frustum[0][1] * _frustum[0][1] + _frustum[0][2] * _frustum[0][2] );
	_frustum[0][0] /= t;
	_frustum[0][1] /= t;
	_frustum[0][2] /= t;
	_frustum[0][3] /= t;

	/* Extract the numbers for the LEFT plane */
	_frustum[1][0] = clip[ 3] + clip[ 0];
	_frustum[1][1] = clip[ 7] + clip[ 4];
	_frustum[1][2] = clip[11] + clip[ 8];
	_frustum[1][3] = clip[15] + clip[12];

	/* Normalize the result */
	t = sqrt( _frustum[1][0] * _frustum[1][0] + _frustum[1][1] * _frustum[1][1] + _frustum[1][2] * _frustum[1][2] );
	_frustum[1][0] /= t;
	_frustum[1][1] /= t;
	_frustum[1][2] /= t;
	_frustum[1][3] /= t;

	/* Extract the BOTTOM plane */
	_frustum[2][0] = clip[ 3] + clip[ 1];
	_frustum[2][1] = clip[ 7] + clip[ 5];
	_frustum[2][2] = clip[11] + clip[ 9];
	_frustum[2][3] = clip[15] + clip[13];

	/* Normalize the result */
	t = sqrt( _frustum[2][0] * _frustum[2][0] + _frustum[2][1] * _frustum[2][1] + _frustum[2][2] * _frustum[2][2] );
	_frustum[2][0] /= t;
	_frustum[2][1] /= t;
	_frustum[2][2] /= t;
	_frustum[2][3] /= t;

	/* Extract the TOP plane */
	_frustum[3][0] = clip[ 3] - clip[ 1];
	_frustum[3][1] = clip[ 7] - clip[ 5];
	_frustum[3][2] = clip[11] - clip[ 9];
	_frustum[3][3] = clip[15] - clip[13];

	/* Normalize the result */
	t = sqrt( _frustum[3][0] * _frustum[3][0] + _frustum[3][1] * _frustum[3][1] + _frustum[3][2] * _frustum[3][2] );
	_frustum[3][0] /= t;
	_frustum[3][1] /= t;
	_frustum[3][2] /= t;
	_frustum[3][3] /= t;

	/* Extract the FAR plane */
	_frustum[4][0] = clip[ 3] - clip[ 2];
	_frustum[4][1] = clip[ 7] - clip[ 6];
	_frustum[4][2] = clip[11] - clip[10];
	_frustum[4][3] = clip[15] - clip[14];

	/* Normalize the result */
	t = sqrt( _frustum[4][0] * _frustum[4][0] + _frustum[4][1] * _frustum[4][1] + _frustum[4][2] * _frustum[4][2] );
	_frustum[4][0] /= t;
	_frustum[4][1] /= t;
	_frustum[4][2] /= t;
	_frustum[4][3] /= t;

	/* Extract the NEAR plane */
	_frustum[5][0] = clip[ 3] + clip[ 2];
	_frustum[5][1] = clip[ 7] + clip[ 6];
	_frustum[5][2] = clip[11] + clip[10];
	_frustum[5][3] = clip[15] + clip[14];

	/* Normalize the result */
	t = sqrt( _frustum[5][0] * _frustum[5][0] + _frustum[5][1] * _frustum[5][1] + _frustum[5][2] * _frustum[5][2] );
	_frustum[5][0] /= t;
	_frustum[5][1] /= t;
	_frustum[5][2] /= t;
	_frustum[5][3] /= t;
}

//int CubeInFrustum( float x, float y, float z, float size )
bool Frustum::CubeInFrustum( vector3d centro, float alto, float largo, float ancho )
{
	int p;

	for( p = 0; p < 6; p++ )
	{
		if( _frustum[p][0] * (centro.getX() - ancho) + _frustum[p][1] * (centro.getY() - alto) + _frustum[p][2] * (centro.getZ() - largo) + _frustum[p][3] > 0 )
			continue;
		if( _frustum[p][0] * (centro.getX() + ancho) + _frustum[p][1] * (centro.getY() - alto) + _frustum[p][2] * (centro.getZ() - largo) + _frustum[p][3] > 0 )
			continue;
		if( _frustum[p][0] * (centro.getX() - ancho) + _frustum[p][1] * (centro.getY() + alto) + _frustum[p][2] * (centro.getZ() - largo) + _frustum[p][3] > 0 )
			continue;
		if( _frustum[p][0] * (centro.getX() + ancho) + _frustum[p][1] * (centro.getY() + alto) + _frustum[p][2] * (centro.getZ() - largo) + _frustum[p][3] > 0 )
			continue;
		if( _frustum[p][0] * (centro.getX() - ancho) + _frustum[p][1] * (centro.getY() - alto) + _frustum[p][2] * (centro.getZ() + largo) + _frustum[p][3] > 0 )
			continue;
		if( _frustum[p][0] * (centro.getX() + ancho) + _frustum[p][1] * (centro.getY() - alto) + _frustum[p][2] * (centro.getZ() + largo) + _frustum[p][3] > 0 )
			continue;
		if( _frustum[p][0] * (centro.getX() - ancho) + _frustum[p][1] * (centro.getY() + alto) + _frustum[p][2] * (centro.getZ() + largo) + _frustum[p][3] > 0 )
			continue;
		if( _frustum[p][0] * (centro.getX() + ancho) + _frustum[p][1] * (centro.getY() + alto) + _frustum[p][2] * (centro.getZ() + largo) + _frustum[p][3] > 0 )
			continue;
		return false;
	}
	return true;
}

int Frustum::CubeInFrustum2( vector3d centro, float alto, float largo, float ancho )
{
	int p;
	int c;
	int c2 = 0;

	for( p = 0; p < 6; p++ )
	{
		c = 0;
		if( _frustum[p][0] * (centro.getX() - ancho) + _frustum[p][1] * (centro.getY() - alto) + _frustum[p][2] * (centro.getZ() - largo) + _frustum[p][3] > 0 )
			c++;
		if( _frustum[p][0] * (centro.getX() + ancho) + _frustum[p][1] * (centro.getY() - alto) + _frustum[p][2] * (centro.getZ() - largo) + _frustum[p][3] > 0 )
			c++;
		if( _frustum[p][0] * (centro.getX() - ancho) + _frustum[p][1] * (centro.getY() + alto) + _frustum[p][2] * (centro.getZ() - largo) + _frustum[p][3] > 0 )
			c++;
		if( _frustum[p][0] * (centro.getX() + ancho) + _frustum[p][1] * (centro.getY() + alto) + _frustum[p][2] * (centro.getZ() - largo) + _frustum[p][3] > 0 )
			c++;
		if( _frustum[p][0] * (centro.getX() - ancho) + _frustum[p][1] * (centro.getY() - alto) + _frustum[p][2] * (centro.getZ() + largo) + _frustum[p][3] > 0 )
			c++;
		if( _frustum[p][0] * (centro.getX() + ancho) + _frustum[p][1] * (centro.getY() - alto) + _frustum[p][2] * (centro.getZ() + largo) + _frustum[p][3] > 0 )
			c++;
		if( _frustum[p][0] * (centro.getX() - ancho) + _frustum[p][1] * (centro.getY() + alto) + _frustum[p][2] * (centro.getZ() + largo) + _frustum[p][3] > 0 )
			c++;
		if( _frustum[p][0] * (centro.getX() + ancho) + _frustum[p][1] * (centro.getY() + alto) + _frustum[p][2] * (centro.getZ() + largo) + _frustum[p][3] > 0 )
			c++;
		if( c == 0 )
			return 0;
		if( c == 8 )
			c2++;
	}
	return (c2 == 6) ? 2 : 1;
}

bool Frustum::sphereInFrustum(Esfera esfera/*vector3d centro, float radio*/)
{
	for(int i = 0; i < 6; i++)
		if( _frustum[i][0] * esfera.getVector3d().getX() + _frustum[i][1] * esfera.getVector3d().getY() + _frustum[i][2] * esfera.getVector3d().getZ() + _frustum[i][3] <= -esfera.getRadio() )
			return false;
	return true;
}

bool Frustum::PointInFrustum(vector3d punto)
{
	for(int i = 0; i < 6; i++)
		if( _frustum[i][0] * punto.getX() + _frustum[i][1] * punto.getY() + _frustum[i][2] * punto.getZ() + _frustum[i][3] <= 0 )
			return false;
	return true;
}

}
