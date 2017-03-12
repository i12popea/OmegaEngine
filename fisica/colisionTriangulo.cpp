#include "colisionTriangulo.hpp"

using namespace std;
using namespace ed;

namespace ed{

/*void ordenar(float a, float b)
{
	if(a > b)
	{
		float c;
		c = a;
		a = b;
		b = c;
	}
}*/
void ordenar(vector2d &vector)
{
	if(vector.getU() > vector.getV())
	{
		float c;
		c = vector.getU();
		vector.setU(vector.getV());
		vector.setV(c);
	}
}

bool edge_edge_test(vector3d &V0, vector3d &U0, vector3d &U1, float i0, float i1, float Ax, float Ay)
{
	float Bx, By, Cx, Cy, e, d, f;
	bool bandera = false;
	vector<float> vectorU0; vectorU0.push_back(U0.getX()); vectorU0.push_back(U0.getY()); vectorU0.push_back(U0.getZ());
	vector<float> vectorU1; vectorU1.push_back(U1.getX()); vectorU1.push_back(U1.getY()); vectorU1.push_back(U1.getZ());
	vector<float> vectorV0; vectorV0.push_back(V0.getX()); vectorV0.push_back(V0.getY()); vectorV0.push_back(V0.getZ());
	/*float vectorU0[] = {U0.getX(), U0.getY(), U0.getZ()};
	float vectorU1[] = {U1.getX(), U1.getY(), U1.getZ()};
	float vectorV0[] = {V0.getX(), V0.getY(), V0.getZ()};*/
	Bx = vectorU0[i0] - vectorU1[i0];
	By = vectorU0[i1] - vectorU1[i1];
	Cx = vectorV0[i0] - vectorU0[i0];
	Cy = vectorV0[i1] - vectorU0[i1];
	f = Ay*Bx-Ax*By;
	d = By*Cx-Bx*Cy;
	if((f > 0 && d >= 0 && d <= f) || (f < 0 && d <= 0 && d >= f))
	{
		e = Ax*Cy-Ay*Cx;
		if(f > 0)
		{
			if(e >= 0 && e <= f) bandera = true;//return 1;
		}
		else
		{
			if(e <= 0 && e >= f) bandera = true;//return 1;
		}
	}
	return bandera;
}

bool edge_against_tri_edges(vector3d &V0, vector3d &V1, vector3d &U0, vector3d &U1, vector3d &U2, float i0, float i1)
{
	float Ax, Ay;//, Bx, By, Cx, Cy, e, d, f;
	vector<float> vectorV0; vectorV0.push_back(V0.getX()); vectorV0.push_back(V0.getY()); vectorV0.push_back(V0.getZ());
	vector<float> vectorV1; vectorV1.push_back(V1.getX()); vectorV1.push_back(V1.getY()); vectorV1.push_back(V1.getZ());
	//float vectorV0[] = {V0.getX(), V0.getY(), V0.getZ()};
	//float vectorV1[] = {V1.getX(), V1.getY(), V1.getZ()};
	Ax = vectorV1[i0] - vectorV0[i0];
	Ay = vectorV1[i1] - vectorV0[i1];
	/* test edge U0,U1 against V0,V1 */
	if(edge_edge_test(V0, U0, U1, i0, i1, Ax, Ay))
		return true;
	/* test edge U1,U2 against V0,V1 */
	if(edge_edge_test(V0, U1, U2, i0, i1, Ax, Ay))
		return true;
	/* test edge U2,U1 against V0,V1 */
	if(edge_edge_test(V0, U2, U0, i0, i1, Ax, Ay))
		return true;

	return false;
}

bool point_in_tri(vector3d V0, vector3d U0, vector3d U1, vector3d U2, float i0, float i1)
{
	bool bandera = false;
	float a, b, c, d0, d1, d2;
	vector<float> vectorV0; vectorV0.push_back(V0.getX()); vectorV0.push_back(V0.getY()); vectorV0.push_back(V0.getZ());
	vector<float> vectorU0; vectorU0.push_back(U0.getX()); vectorU0.push_back(U0.getY()); vectorU0.push_back(U0.getZ());
	vector<float> vectorU1; vectorU1.push_back(U1.getX()); vectorU1.push_back(U1.getY()); vectorU1.push_back(U1.getZ());
	vector<float> vectorU2; vectorU2.push_back(U2.getX()); vectorU2.push_back(U2.getY()); vectorU2.push_back(U2.getZ());
	/*float vectorV0[] = {V0.getX(), V0.getY(), V0.getZ()};
	float vectorU0[] = {U0.getX(), U0.getY(), U0.getZ()};
	float vectorU1[] = {U1.getX(), U1.getY(), U1.getZ()};
	float vectorU2[] = {U2.getX(), U2.getY(), U2.getZ()};*/
	/* is T1 completly inside T2? */
	/* check if V0 is inside tri(U0,U1,U2) */
	a = vectorU1[i1] - vectorU0[i1];
	b = -(vectorU1[i0] - vectorU0[i0]);
	c = -a*vectorU0[i0] - b*vectorU0[i1];
	d0 = a*vectorV0[i0] + b*vectorV0[i1]+c;

	a = vectorU2[i1] - vectorU1[i1];
	b = -(vectorU2[i0] - vectorU1[i0]);
	c = -a*vectorU1[i0] - b*vectorU1[i1];
	d1 = a*vectorV0[i0] + b*vectorV0[i1]+c;

	a = vectorU0[i1] - vectorU2[i1];
	b = -(vectorU0[i0] - vectorU2[i0]);
	c = -a*vectorU2[i0] - b*vectorU2[i1];
	d2 = a*vectorV0[i0] + b*vectorV0[i1]+c;

	if(d0*d1 > 0.0)
	{
		if(d0*d2 > 0.0) bandera = true;//return 1;
	}
	return bandera;
}

bool coplanar_tri_tri(vector3d N, vector3d V0, vector3d V1, vector3d V2, vector3d U0, vector3d U1, vector3d U2)
{
	vector3d A;
	short i0, i1;
	/* first project onto an axis-aligned plane, that maximizes the area */
	/* of the triangles, compute indices: i0,i1. */
	A.setX(float(fabs(N.getX())));
	A.setY(float(fabs(N.getY())));
	A.setZ(float(fabs(N.getZ())));
	if(A.getX() > A.getY())
	{
		if(A.getX() > A.getZ())
		{
			i0 = 1;      /* A[0] is greatest */
			i1 = 2;
		}
		else
		{
			i0 = 0;      /* A[2] is greatest */
			i1 = 1;
		}
	}
	else   /* A[0]<=A[1] */
	{
		if(A.getZ() > A.getY())
		{
			i0 = 0;      /* A[2] is greatest */
			i1 = 1;
		}
		else
		{
			i0 = 0;      /* A[1] is greatest */
			i1 = 2;
		}
	}

	/* test all edges of triangle 1 against the edges of triangle 2 */
	if(edge_against_tri_edges(V0, V1, U0, U1, U2, i0, i1))
		return true;
	if(edge_against_tri_edges(V1, V2, U0, U1, U2, i0, i1))
		return true;
	if(edge_against_tri_edges(V2, V0, U0, U1, U2, i0, i1))
		return true;

	/* finally, test if tri1 is totally contained in tri2 or vice versa */
	if(point_in_tri(V0, U0, U1, U2, i0, i1))
		return true;

	if(point_in_tri(U0, V0, V1, V2, i0, i1))
		return true;

	return false;
}

void newcompute_intervals(float VV0, float VV1, float VV2, float D0, float D1, float D2, float D0D1, float D0D2, float &A, float &B, float &C, float &X0, float &X1, bool &coplanar)
{
	coplanar = false;
	if(D0D1 > 0.0f)
	{
		/* here we know that D0D2<=0.0 */
		/* that is D0, D1 are on the same side, D2 on the other or on the plane */
		A=VV2; B=(VV0-VV2)*D2; C=(VV1-VV2)*D2; X0=D2-D0; X1=D2-D1;
	}
	else if(D0D2 > 0.0f)
	{
		/* here we know that d0d1<=0.0 */
		A=VV1; B=(VV0-VV1)*D1; C=(VV2-VV1)*D1; X0=D1-D0; X1=D1-D2;
	}
	else if(D1*D2 > 0.0f || D0 != 0.0f)
	{
		/* here we know that d0d1<=0.0 or that D0!=0.0 */
		A=VV0; B=(VV1-VV0)*D0; C=(VV2-VV0)*D0; X0=D0-D1; X1=D0-D2;
	}
	else if(D1 != 0.0f)
	{
		A=VV1; B=(VV0-VV1)*D1; C=(VV2-VV1)*D1; X0=D1-D0; X1=D1-D2;
	}
	else if(D2 != 0.0f)
	{
		A=VV2; B=(VV0-VV2)*D2; C=(VV1-VV2)*D2; X0=D2-D0; X1=D2-D1;
	}
	else
	{
		/* triangles are coplanar */
		coplanar = true;
		//return coplanar_tri_tri(N1, V0, V1, V2, U0, U1, U2);
	}
}

bool interseccionTriangulo(vector3d V0, vector3d V1, vector3d V2, vector3d U0, vector3d U1, vector3d U2)
{
	vector3d E1, E2;
	vector3d N1, N2;
	float d1, d2;
	float du0, du1, du2, dv0, dv1, dv2;
	vector3d D;
	vector2d isect1, isect2;
	float du0du1, du0du2, dv0dv1, dv0dv2;
	short index;
	float vp0, vp1, vp2;
	float up0, up1, up2;
	float bb, cc, max;
	bool coplanar1, coplanar2;
	vector<float> vectorV0; vectorV0.push_back(V0.getX()); vectorV0.push_back(V0.getY()); vectorV0.push_back(V0.getZ());
	vector<float> vectorV1; vectorV1.push_back(V1.getX()); vectorV1.push_back(V1.getY()); vectorV1.push_back(V1.getZ());
	vector<float> vectorV2; vectorV2.push_back(V2.getX()); vectorV2.push_back(V2.getY()); vectorV2.push_back(V2.getZ());
	vector<float> vectorU0; vectorU0.push_back(U0.getX()); vectorU0.push_back(U0.getY()); vectorU0.push_back(U0.getZ());
	vector<float> vectorU1; vectorU1.push_back(U1.getX()); vectorU1.push_back(U1.getY()); vectorU1.push_back(U1.getZ());
	vector<float> vectorU2; vectorU2.push_back(U2.getX()); vectorU2.push_back(U2.getY()); vectorU2.push_back(U2.getZ());
	/*float vectorV0[] = {V0.getX(), V0.getY(), V0.getZ()};
	float vectorV1[] = {V1.getX(), V1.getY(), V1.getZ()};
	float vectorV2[] = {V2.getX(), V2.getY(), V2.getZ()};
	float vectorU0[] = {U0.getX(), U0.getY(), U0.getZ()};
	float vectorU1[] = {U1.getX(), U1.getY(), U1.getZ()};
	float vectorU2[] = {U2.getX(), U2.getY(), U2.getZ()};*/

	/* compute plane equation of triangle(V0,V1,V2) */
	E1 = V1 - V0;
	E2 = V2 - V0;
	N1 = productoVectorial(E1, E2);
	d1 = -productoEscalar(N1, V0);
	/* plane equation 1: N1.X+d1=0 */

	/* put U0,U1,U2 into plane equation 1 to compute signed distances to the plane*/
	du0 = productoEscalar(N1, U0) + d1;
	du1 = productoEscalar(N1, U1) + d1;
	du2 = productoEscalar(N1, U2) + d1;

	/* coplanarity robustness check */
	if(float(fabs(du0)) < EPSILON) du0 = 0.0;
	if(float(fabs(du1)) < EPSILON) du1 = 0.0;
	if(float(fabs(du2)) < EPSILON) du2 = 0.0;

	du0du1 = du0*du1;
	du0du2 = du0*du2;

	if(du0du1 > 0.0f && du0du2 > 0.0f) /* same sign on all of them + not equal 0 ? */
		return false;                    /* no intersection occurs */

	/* compute plane of triangle (U0,U1,U2) */
	E1 = U1 - U0;
	E2 = U2 - U0;
	N2 = productoVectorial(E1, E2);
	d2 = -productoEscalar(N2, U0);
	/* plane equation 2: N2.X+d2=0 */

	/* put V0,V1,V2 into plane equation 2 */
	dv0 = productoEscalar(N2, V0) + d2;
	dv1 = productoEscalar(N2, V1) + d2;
	dv2 = productoEscalar(N2, V2) + d2;

	if(float(fabs(dv0))<EPSILON) dv0 = 0.0;
	if(float(fabs(dv1))<EPSILON) dv1 = 0.0;
	if(float(fabs(dv2))<EPSILON) dv2 = 0.0;

	dv0dv1 = dv0*dv1;
	dv0dv2 = dv0*dv2;

	if(dv0dv1 > 0.0f && dv0dv2 > 0.0f) /* same sign on all of them + not equal 0 ? */
		return false;                    /* no intersection occurs */

	/* compute direction of intersection line */
	D = productoVectorial(N1, N2);

	/* compute and index to the largest component of D */
	max = float(fabs(D.getX()));
	index = 0;
	bb = float(fabs(D.getY()));
	cc = float(fabs(D.getZ()));
	if(bb > max) max = bb,index = 1;
	if(cc > max) max = cc,index = 2;

	/* this is the simplified projection onto L*/
	vp0 = vectorV0[index];
	vp1 = vectorV1[index];
	vp2 = vectorV2[index];

	up0 = vectorU0[index];
	up1 = vectorU1[index];
	up2 = vectorU2[index];

	/* compute interval for triangle 1 */
	float a,b,c,x0,x1;
	newcompute_intervals(vp0, vp1, vp2, dv0, dv1, dv2, dv0dv1, dv0dv2, a, b, c, x0, x1, coplanar1);
	if(coplanar1)
		return coplanar_tri_tri(N1, V0, V1, V2, U0, U1, U2);

	/* compute interval for triangle 2 */
	float d,e,f,y0,y1;
	newcompute_intervals(up0, up1, up2, du0, du1, du2, du0du1, du0du2, d, e, f, y0, y1, coplanar2);
	if(coplanar2)
		return coplanar_tri_tri(N1, V0, V1, V2, U0, U1, U2);

	float xx,yy,xxyy,tmp;
	xx = x0*x1;
	yy = y0*y1;
	xxyy = xx*yy;

	tmp = a*xxyy;
	isect1.setU(tmp+b*x1*yy);
	isect1.setV(tmp+c*x0*yy);

	tmp = d*xxyy;
	isect2.setU(tmp+e*xx*y1);
	isect2.setV(tmp+f*xx*y0);

	ordenar(isect1);
	ordenar(isect2);

	if(isect1.getV() < isect2.getU() || isect2.getV() < isect1.getU()) return false;
	return true;
}

}
