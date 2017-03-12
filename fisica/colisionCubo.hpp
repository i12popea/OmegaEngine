#ifndef _COLISIONCUBO_HPP_
#define _COLISIONCUBO_HPP_

#include <iostream>
#include <vector>
#include "../vector3d.hpp"

using std::vector;

namespace ed{

class Box{
	private:
		vector3d _coordenadas;
		float _alto; //Para Y
		float _largo; //Para Z 
		float _ancho; //Para X
	public:
		Box(vector3d vector=vector3d(0, 0, 0), float alto=0, float largo=0, float ancho=0);
		/*Rectangulo(vector3d vector=0, float alto=0, float ancho=0)
		{
			setVector3d(vector);
			setAlto(alto);
			setAncho(ancho);
		}*/
		inline float getAlto() const
		{
			return _alto;
		}
		inline float getLargo() const
		{
			return _largo;
		}
		inline float getAncho() const
		{
			return _ancho;
		}

		inline void setAlto(float alto)
		{
			_alto=alto;
		}
		inline void setLargo(float largo)
		{
			_largo=largo;
		}
		inline void setAncho(float ancho)
		{
			_ancho=ancho;
		}

		inline vector3d getVector3d()
		{
			return _coordenadas;
		}
		inline void setVector3d(vector3d vector)
		{
			//_coordenadas=vector;
			_coordenadas.setX(vector.getX());
			_coordenadas.setY(vector.getY());
			_coordenadas.setZ(vector.getZ());
		}

		Box& operator = (const Box &box);
		vector<vector3d> trianguloBox();
		vector3d getVertexP(vector3d &normal);
		vector3d getVertexN(vector3d &normal);

};

//bool interseccion(Rectangulo uno, Rectangulo dos);

}

#endif
