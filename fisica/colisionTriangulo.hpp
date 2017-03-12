#ifndef _COLISIONTRIANGULO_HPP_
#define _COLISIONTRIANGULO_HPP_

#include "../vector3d.hpp"
#include <vector>

using namespace std;
using namespace ed;
using std::vector;

namespace ed{

#define EPSILON 0.000001

void ordenar(vector2d &vector);

bool edge_edge_test(vector3d &V0, vector3d &U0, vector3d &U1, float i0, float i1, float Ax, float Ay);

bool edge_against_tri_edges(vector3d &V0, vector3d &V1, vector3d &U0, vector3d &U1, vector3d &U2, float i0, float i1);

bool point_in_tri(vector3d V0, vector3d U0, vector3d U1, vector3d U2, float i0, float i1);

bool coplanar_tri_tri(vector3d N, vector3d V0, vector3d V1, vector3d V2, vector3d U0, vector3d U1, vector3d U2);

void newcompute_intervals(float VV0, float VV1, float VV2, float D0, float D1, float D2, float D0D1, float D0D2, float &A, float &B, float &C, float &X0, float &X1, bool &coplanar);

bool interseccionTriangulo(vector3d V0, vector3d V1, vector3d V2, vector3d U0, vector3d U1, vector3d U2);

}

#endif
