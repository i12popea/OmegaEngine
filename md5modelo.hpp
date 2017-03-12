/*
 * md5model.h -- md5mesh model loader + animation
 * last modification: aug. 14, 2007
 *
 * Copyright (c) 2005-2007 David HENRY
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * gcc -Wall -ansi -lGL -lGLU -lglut md5anim.c md5anim.c -o md5model
 */

#ifndef __MD5MODELO_HPP__
#define __MD5MODELO_HPP__

#include "md5animacion.hpp"
#include "quaternion.hpp"
#include <vector>
#include <cstring>
#include <fstream>
#include "textura.hpp"

using namespace std;
using std::vector;
using std::string;

namespace ed{

/* Joint */
struct md5_joint_t
{
	string name;
	int parent;
	vector3d pos;
	quaternion orient;

	md5_joint_t& operator = (const md5_joint_t& joint)
	{
		name = joint.name;
		parent = joint.parent;
		pos = joint.pos;
		orient = joint.orient;
		return *this;
	}
};

/* Vertex */
struct md5_vertex_t
{
	vector3d pos;
	vector3d normal;
	vector2d st;
	int start; /* start weight */
	int count; /* weight count */

	md5_vertex_t& operator = (const md5_vertex_t& vertex)
	{
		pos = vertex.pos;
		normal = vertex.normal;
		st = vertex.st;
		start = vertex.start;
		count = vertex.count;
		return *this;
	}
};

/* Triangle */
struct md5_triangle_t
{
	int index[3];

	md5_triangle_t& operator = (const md5_triangle_t& triangle)
	{
		index[0] = triangle.index[0];
		index[1] = triangle.index[1];
		index[2] = triangle.index[2];
		return *this;
	}
};

/* Weight */
struct md5_weight_t
{
	int joint;
	float bias;
	vector3d pos;

	md5_weight_t& operator = (const md5_weight_t& weight)
	{
		joint = weight.joint;
		bias = weight.bias;
		pos = weight.pos;
		return *this;
	}
};

/* MD5 mesh */
struct md5_mesh_t
{
	GLuint idTexture;

	vector<md5_vertex_t> vertices;
	vector<md5_triangle_t> triangles;
	vector<md5_weight_t> weights;

	int num_verts;
	int num_tris;
	int num_weights;

	string shader;

	vector<vector3d> vertexArray;
	vector<vector3d> verticeArray;
	vector<vector3d> normalArray;
	vector<vector2d> textureArray;
	vector<vector2d> texturaArray;
	vector<GLuint> vertexIndices;

	md5_mesh_t& operator = (const md5_mesh_t& mesh)
	{
		idTexture = mesh.idTexture;
		vertices = mesh.vertices;
		triangles = mesh.triangles;
		weights = mesh.weights;
		num_verts = mesh.num_verts;
		num_tris = mesh.num_tris;
		num_weights = mesh.num_weights;
		shader = mesh.shader;
		vertexArray = mesh.vertexArray;
		normalArray = mesh.normalArray;
		textureArray = mesh.textureArray;
		vertexIndices = mesh.vertexIndices;
		return *this;
	}
};


/* MD5 model structure */
class md5_model_t
{
public:
	vector<md5_joint_t> baseSkel;
	vector<md5_mesh_t> meshes;
	Animacion animacion;
	bool _banderaAnimacion;

	int num_joints;
	int num_meshes;

	md5_model_t()
	{
	}
	inline bool getBanderaAnimacion()
	{
		return _banderaAnimacion;
	}

//md5_model_t & operator = (md5_model_t const &model);
void DrawSkeleton (const vector<md5_joint_t> &skeleton);
void Update(float time);
void PrepareMesh(md5_mesh_t &mesh);
void PrepareMesh(md5_mesh_t &mesh, const vector<skeletonJoint> &skeleton);
void PrepareNormals(md5_mesh_t &mesh);
int ReadMD5Model(string filename);
bool CheckAnimValidity (const Animacion &mdl);
void Render();
void RenderMesh(const md5_mesh_t & mesh);
};

void RemoveQuotes( string& str );
int GetFileLength( istream& file );

}


#endif/*  __MD5MODEL_H__ */
