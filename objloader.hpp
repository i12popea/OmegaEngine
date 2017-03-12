#ifndef _OBJLOADER_HPP_
#define _OBJLOADER_HPP_

#include "shader.hpp" //Para colocar este fichero objloader.hpp debe ir en primer lugar en los ficheros de inclusión de otros ficheros de inclusión
#include <vector>
#include <cstring>
#include <sstream>
#include <fstream>
#include "vector3d.hpp"
#include "indicePlano.hpp"
#include "textura.hpp"
#include "iluminacion.hpp"
#include <GL/glut.h>

using namespace std;
using std::vector;
using std::string;

namespace ed
{

enum TipoObjeto {
	OBJETO = 0,
	DESTRUCTIBLE,
	BOTIQUIN,
	ARMADURA,
	ARMA,
	MUNICION,
	ITEM,
	ESCALON,
	PUERTA,
	VENTANA,
	INTERRUPTOR
};

class Material
{
private:
	string _nombre;
	float _alpha, _ns;
	vector<float> _dif, _amb, _spec;
	int _illum;
	int _id_textura;
public:
	//Constructor
	Material(string nombre, float alpha, float ns, vector<float> dif, vector<float> amb, vector<float> spec, int ilum, int id_textura)
	{
		_nombre = nombre;
		_alpha = alpha;
		_ns = ns;
		_dif = dif;
		_amb = amb;
		_spec = spec;
		_illum = ilum;
		_id_textura = id_textura;
	}

	//Destructor
	~Material()
	{
		_nombre = "";
		_alpha = 0.0;
		_ns = 0.0;
		_dif.erase(_dif.begin(), _dif.end());
		_amb.erase(_amb.begin(), _amb.end());
		_spec.erase(_spec.begin(), _spec.end());
		_illum = 0;
		_id_textura = 0;
	}

	inline void setNombre(string nombre)
	{
		_nombre = nombre;
	}
	inline void setAlpha(float alpha)
	{
		_alpha = alpha;
	}
	inline void setNs(float ns)
	{
		_ns = ns;
	}
	inline void setDif(vector<float> dif)
	{
		_dif = dif;
	}
	inline void setAmb(vector<float> amb)
	{
		_amb = amb;
	}
	inline void setSpec(vector<float> spec)
	{
		_spec = spec;
	}
	inline void setIllum(float illum)
	{
		_illum = illum;
	}
	inline void setIdTextura(float id)
	{
		_id_textura = id;
	}

	inline string getNombre() const
	{
		return _nombre;
	}
	inline float getAlpha() const
	{
		return _alpha;
	}
	inline float getNs() const
	{
		return _ns;
	}
	inline float getDif(int indice) const
	{
		return _dif[indice];
	}
	inline vector<float> getDif() const
	{
		return _dif;
	}
	inline float getAmb(int indice) const
	{
		return _amb[indice];
	}
	inline vector<float> getAmb() const
	{
		return _amb;
	}
	inline float getSpec(int indice) const
	{
		return _spec[indice];
	}
	inline vector<float> getSpec() const
	{
		return _spec;
	}
	inline float getIllum() const
	{
		return _illum;
	}
	inline int getIdTextura() const
	{
		return _id_textura;
	}

	Material& operator = (const Material &m);
};

class Objeto
{
private:
	//bool _banderaAnimacion;
	vector<vector3d> _lista_vertices; //Lista de vertices
	vector<vector3d> _lista_normales; //Lista de normales
	vector<vector2d> _lista_coordenadas; //Lista de coordenadas
	vector<vector3d> _lista_colores; //Lista de colores
	vector<Material> _material;
	vector<string> _nombreMaterial; //Nombre del material usado
	vector<int> _indiceMaterial; //Número de cara registrado
	//Animacion _animacion;
	vector< vector<vector2d> > _matrizCoordenadas;
	vector< vector<vector3d> > _matrizVertices;
	vector< vector<vector3d> > _matrizNormales;
	vector< vector<vector3d> > _matrizColores;
	vector<int> _indicePlano;
	vector<int> _indiceNombre;
public:
	//Constructor
	Objeto()
	{
		//_banderaAnimacion = false;
	}
	//Destructor
	~Objeto()
	{
		_material.erase(_material.begin(), _material.end());
		_nombreMaterial.erase(_nombreMaterial.begin(), _nombreMaterial.end());
		_indiceMaterial.erase(_indiceMaterial.begin(), _indiceMaterial.end());
	}

	//Modificadores
	inline void setMaterial(vector<Material> material)
	{
		_material = material;
	}
	inline void setNombreMaterial(vector<string> nombreMaterial)
	{
		_nombreMaterial = nombreMaterial;
	}
	inline void setIndiceMaterial(vector<int> indiceMaterial)
	{
		_indiceMaterial = indiceMaterial;
	}
	/*inline void setAnimacion(Animacion animacion)
	{
		_animacion = animacion;
	}*/

	//Observadores
	/*inline bool getBanderaAnimacion() const
	{
		return _banderaAnimacion;
	}*/
	inline vector<vector3d> getListaVertices() const
	{
		return _lista_vertices;
	}
	inline vector3d getListaVertices(int indice)
	{
		return _lista_vertices[indice];
	}
	inline vector<Material> getMaterial() const
	{
		return _material;
	}
	inline vector<string> getNombreMaterial() const
	{
		return _nombreMaterial;
	}
	inline vector<int> getIndiceMaterial() const
	{
		return _indiceMaterial;
	}
	/*inline Animacion getAnimacion() const
	{
		return _animacion;
	}*/

	Objeto& operator = (const Objeto &o);

	//Metodos
	void PrepararShader(Shader &shader, int textura, GLfloat LightPosition[], GLfloat LightColor[], int CantidadLuces);
	void CargaOBJ(string archivo);
	bool CargaMTL(string archivo);
	void dibujar(Shader &shader, GLfloat LightPosition[], GLfloat LightColor[], int CantidadLuces);
	void dibujar();
	//void ProcesarModelo(vector<vector3d> &mesh, vector<vector2d> &meshCoord, vector<vector3d> &meshNormal, const vector<skeletonJoint> &skeleton, vector<Weight> weights, vector<vector2d> coordAnim, vector<int> starts, vector<int> counts, vector<int> indiceVertices);
	//void Actualizar(float tiempo);
	void CrearIndices(vector<string> &temp_nombreUSEMTL, vector<int> &temp_indiceNombre, vector<int> &temp_indicePlano, vector<IndicePlano> planos);
	void CrearListas(vector<int> temp_indiceNombre, vector<int> temp_indicePlano, vector<vector3d> vertices, vector<vector3d> normales, vector<vector2d> coordenadas, vector<IndicePlano> planos, vector<IndicePlano> planoNormales, vector<IndicePlano> planoCoordenadas);
	void CrearMatricesElementos();
	void CrearVectorNormal(vector<vector3d> vertices, vector<vector3d> &normales, vector<IndicePlano> &planos, vector<IndicePlano> &planoNormales);
};

vector<float> vectorDeCadena(string cadena, string delimitador);

}

#endif
