#ifndef _INDICEPLANO_HPP_
#define _INDICEPLANO_HPP_

#include <iostream>
#include "vector3d.hpp"

namespace ed{

class IndicePlano{
	private:
		int _a;
		int _b;
		int _c; // Se usaran 3 puntos para describir un plano
	public:

		IndicePlano(int a=0, int b=0, int c=0);

		inline int getPuntoA() const
		{
			return _a;
		}
		inline int getPuntoB() const
		{
			return _b;
		}
		inline int getPuntoC() const
		{
			return _c;
		}
		
		inline void setPuntoA(int a)
		{
			_a = a;
		}
		inline void setPuntoB(int b)
		{
			_b = b;
		}
		inline void setPuntoC(int c)
		{
			_c = c;
		}
		/*inline void setVector3d(vector3d vector)
		{
			//_coordenadas=vector;
			_coordenadas.setX(vector.getX());
			_coordenadas.setY(vector.getY());
			_coordenadas.setZ(vector.getZ());
		}*/

};



}

#endif
