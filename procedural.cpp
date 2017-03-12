#include "procedural.hpp"

using namespace std;
using namespace ed;

vector<vector3d> hierba1;
vector<vector3d> hierba2;
vector<vector3d> hierba3;
vector<vector3d> hierba4;
vector<vector3d> hierba5;
vector<vector3d> hierba6;
vector<vector3d> color1;
vector<vector3d> color2;

//vector<vector3d> cesped, colorCesped;

vector<vector3d> suma(vector<vector3d> hierba, vector3d posicion)
{
	for(unsigned int i = 0; i < hierba.size(); i++)
	{
		hierba[i] = hierba[i] + posicion;
	}
	return hierba;
}

void InicializarHierba1()
{
	hierba1.push_back(vector3d(0, 0, 0));
	hierba1.push_back(vector3d(0.1, 0, 0));
	hierba1.push_back(vector3d(0, 0.2, 0));

	hierba1.push_back(vector3d(0.1, 0, 0));
	hierba1.push_back(vector3d(0.1, 0.2, 0));
	hierba1.push_back(vector3d(0, 0.2, 0));

	hierba1.push_back(vector3d(0, 0.2, 0));
	hierba1.push_back(vector3d(0.1, 0.2, 0));
	hierba1.push_back(vector3d(0, 0.4, 0));

	hierba1.push_back(vector3d(0.1, 0.2, 0));
	hierba1.push_back(vector3d(0.1, 0.4, 0));
	hierba1.push_back(vector3d(0, 0.4, 0));

	hierba1.push_back(vector3d(0.1, 0.4, 0));
	hierba1.push_back(vector3d(0.1, 0.5, 0));
	hierba1.push_back(vector3d(0, 0.4, 0));
}

void InicializarHierba2()
{
	hierba2.push_back(vector3d(0, 0, 0));
	hierba2.push_back(vector3d(0, 0, 0.1));
	hierba2.push_back(vector3d(0, 0.2, 0));

	hierba2.push_back(vector3d(0, 0, 0.1));
	hierba2.push_back(vector3d(0, 0.2, 0.1));
	hierba2.push_back(vector3d(0, 0.2, 0));

	hierba2.push_back(vector3d(0, 0.2, 0));
	hierba2.push_back(vector3d(0, 0.2, 0.1));
	hierba2.push_back(vector3d(0, 0.4, 0));

	hierba2.push_back(vector3d(0, 0.2, 0.1));
	hierba2.push_back(vector3d(0, 0.4, 0.1));
	hierba2.push_back(vector3d(0, 0.4, 0));

	hierba2.push_back(vector3d(0, 0.4, 0.1));
	hierba2.push_back(vector3d(0, 0.5, 0.1));
	hierba2.push_back(vector3d(0, 0.4, 0));
}

void InicializarHierba3()
{
	hierba3.push_back(vector3d(0, 0, 0));
	hierba3.push_back(vector3d(0.1, 0, 0));
	hierba3.push_back(vector3d(0.05, 0.2, 0));

	hierba3.push_back(vector3d(0.1, 0, 0));
	hierba3.push_back(vector3d(0.15, 0.2, 0));
	hierba3.push_back(vector3d(0.05, 0.2, 0));

	hierba3.push_back(vector3d(0.05, 0.2, 0));
	hierba3.push_back(vector3d(0.15, 0.2, 0));
	hierba3.push_back(vector3d(0.15, 0.4, 0));

	hierba3.push_back(vector3d(0.15, 0.2, 0));
	hierba3.push_back(vector3d(0.20, 0.4, 0));
	hierba3.push_back(vector3d(0.15, 0.4, 0));

	hierba3.push_back(vector3d(0.20, 0.4, 0));
	hierba3.push_back(vector3d(0.35, 0.5, 0));
	hierba3.push_back(vector3d(0.15, 0.4, 0));
}

void InicializarHierba4()
{
	hierba4.push_back(vector3d(0, 0, 0));
	hierba4.push_back(vector3d(0, 0, 0.1));
	hierba4.push_back(vector3d(0, 0.2, 0.05));

	hierba4.push_back(vector3d(0, 0, 0.1));
	hierba4.push_back(vector3d(0, 0.2, 0.15));
	hierba4.push_back(vector3d(0, 0.2, 0.05));

	hierba4.push_back(vector3d(0, 0.2, 0.05));
	hierba4.push_back(vector3d(0, 0.2, 0.15));
	hierba4.push_back(vector3d(0, 0.4, 0.15));

	hierba4.push_back(vector3d(0, 0.2, 0.15));
	hierba4.push_back(vector3d(0, 0.4, 0.20));
	hierba4.push_back(vector3d(0, 0.4, 0.15));

	hierba4.push_back(vector3d(0, 0.4, 0.20));
	hierba4.push_back(vector3d(0, 0.5, 0.35));
	hierba4.push_back(vector3d(0, 0.4, 0.15));
}

void InicializarHierba5()
{
	hierba5.push_back(vector3d(0, 0, 0));
	hierba5.push_back(vector3d(0, 0.2, 0));
	hierba5.push_back(vector3d(-0.05, 0.2, 0));

	hierba5.push_back(vector3d(0, 0, 0));
	hierba5.push_back(vector3d(0.05, 0, 0));
	hierba5.push_back(vector3d(0, 0.2, 0));

	hierba5.push_back(vector3d(0.05, 0, 0));
	hierba5.push_back(vector3d(0.05, 0.3, 0));
	hierba5.push_back(vector3d(0, 0, 0));

	hierba5.push_back(vector3d(0.05, 0, 0));
	hierba5.push_back(vector3d(0.1, 0.3, 0));
	hierba5.push_back(vector3d(0.05, 0.3, 0));

	hierba5.push_back(vector3d(0.1, 0.3, 0));
	hierba5.push_back(vector3d(0.15, 0.4, 0));
	hierba5.push_back(vector3d(0.05, 0.3, 0));
}

void InicializarHierba6()
{
	hierba6.push_back(vector3d(0, 0, 0));
	hierba6.push_back(vector3d(0, 0.2, 0));
	hierba6.push_back(vector3d(0, 0.2, -0.05));

	hierba6.push_back(vector3d(0, 0, 0));
	hierba6.push_back(vector3d(0, 0, 0.05));
	hierba6.push_back(vector3d(0, 0.2, 0));

	hierba6.push_back(vector3d(0, 0, 0.05));
	hierba6.push_back(vector3d(0, 0.3, 0.05));
	hierba6.push_back(vector3d(0, 0, 0));

	hierba6.push_back(vector3d(0, 0, 0.05));
	hierba6.push_back(vector3d(0, 0.3, 0.1));
	hierba6.push_back(vector3d(0, 0.3, 0.05));

	hierba6.push_back(vector3d(0, 0.3, 0.1));
	hierba6.push_back(vector3d(0, 0.4, 0.15));
	hierba6.push_back(vector3d(0, 0.3, 0.05));
}

void InicializarColor1()
{
	color1.push_back(vector3d(0, 0.5, 0));
	color1.push_back(vector3d(0, 0.5, 0));
	color1.push_back(vector3d(0, 0.75, 0));

	color1.push_back(vector3d(0, 0.5, 0));
	color1.push_back(vector3d(0, 0.75, 0));
	color1.push_back(vector3d(0, 0.75, 0));

	color1.push_back(vector3d(0, 0.75, 0));
	color1.push_back(vector3d(0, 0.75, 0));
	color1.push_back(vector3d(0, 1, 0));

	color1.push_back(vector3d(0, 0.75, 0));
	color1.push_back(vector3d(0, 1, 0));
	color1.push_back(vector3d(0, 1, 0));

	color1.push_back(vector3d(0, 1, 0));
	color1.push_back(vector3d(0, 1.25, 0));
	color1.push_back(vector3d(0, 1, 0));
}

void InicializarColor2()
{
	color2.push_back(vector3d(0, 0.5, 0));
	color2.push_back(vector3d(0, 0.5, 0));
	color2.push_back(vector3d(0, 0.75, 0));

	color2.push_back(vector3d(0, 0.5, 0));
	color2.push_back(vector3d(0, 0.5, 0));
	color2.push_back(vector3d(0, 0.75, 0));

	color2.push_back(vector3d(0, 0.5, 0));
	color2.push_back(vector3d(0, 0.75, 0));
	color2.push_back(vector3d(0, 0.5, 0));

	color2.push_back(vector3d(0, 0.5, 0));
	color2.push_back(vector3d(0, 0.75, 0));
	color2.push_back(vector3d(0, 0.75, 0));

	color2.push_back(vector3d(0, 0.75, 0));
	color2.push_back(vector3d(0, 1, 0));
	color2.push_back(vector3d(0, 0.75, 0));
}

void IniciarHierba()
{
	InicializarHierba1();
	InicializarHierba2();
	InicializarHierba3();
	InicializarHierba4();
	InicializarHierba5();
	InicializarHierba6();
	InicializarColor1();
	InicializarColor2();
}

void CrearCesped(vector3d inicio, vector3d fin, vector<vector3d> &cesped, vector<vector3d> &colorCesped)
{
	//vector<vector3d> cesped;
	/*float intervaloX, intervaloZ;
	intervaloX = (fin.getX() - inicio.getX())/10;
	intervaloZ = (fin.getZ() - inicio.getZ())/10;*/

	if(fin.getY() == inicio.getY())
	{
		for(float i = inicio.getX(); i < fin.getX(); i = i + 0.15)
		{
			for(float j = inicio.getZ(); j < fin.getZ(); j = j + 0.15)
			{
				//Iniciamos una semilla aleatoria
				srand(time(NULL));
				//Escogemos una cantidad entre 1 y 6
				int tipo = 1 + ( rand() % ( 6 - 1 + 1 ) );

				vector<vector3d> hierba, color;

				if(tipo == 1)
				{
					hierba = suma(hierba1, vector3d(i, fin.getY(), j));
					color = color1;
				}
				if(tipo == 2)
				{
					hierba = suma(hierba2, vector3d(i, fin.getY(), j));
					color = color1;
				}
				if(tipo == 3)
				{
					hierba = suma(hierba3, vector3d(i, fin.getY(), j));
					color = color1;
				}
				if(tipo == 4)
				{
					hierba = suma(hierba4, vector3d(i, fin.getY(), j));
					color = color1;
				}
				if(tipo == 5)
				{
					hierba = suma(hierba5, vector3d(i, fin.getY(), j));
					color = color1;
				}
				if(tipo == 6)
				{
					hierba = suma(hierba6, vector3d(i, fin.getY(), j));
					color = color2;
				}
				cesped.insert(cesped.end(), hierba.begin(), hierba.end());
				colorCesped.insert(colorCesped.end(), color.begin(), color.end());
			}
		}
	}
	else
	{
		for(int i = inicio.getX(); i < fin.getX(); i = i + 0.15)
		{
			for(int j = inicio.getZ(); j < fin.getZ(); j = j + 0.15)
			{
				for(int k = inicio.getY(); k < fin.getY(); k = k + 0.15)
				{
					//Iniciamos una semilla aleatoria
					srand(time(NULL));
					//Escogemos una cantidad entre 1 y 6
					int tipo = 1 + ( rand() % ( 6 - 1 + 1 ) );

					vector<vector3d> hierba, color;

					if(tipo == 1)
					{
						hierba = suma(hierba1, vector3d(i, k, j));
						color = color1;
					}
					if(tipo == 2)
					{
						hierba = suma(hierba2, vector3d(i, k, j));
						color = color1;
					}
					if(tipo == 3)
					{
						hierba = suma(hierba3, vector3d(i, k, j));
						color = color1;
					}
					if(tipo == 4)
					{
						hierba = suma(hierba4, vector3d(i, k, j));
						color = color1;
					}
					if(tipo == 5)
					{
						hierba = suma(hierba5, vector3d(i, k, j));
						color = color1;
					}
					if(tipo == 6)
					{
						hierba = suma(hierba6, vector3d(i, k, j));
						color = color2;
					}
					cesped.insert(cesped.end(), hierba.begin(), hierba.end());
					colorCesped.insert(colorCesped.end(), color.begin(), color.end());
				}
			}
		}
	}
}

void RenderizarCesped(vector<vector3d> cesped, vector<vector3d> colorCesped)
{
	glPushMatrix();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(vector3d), &cesped[0]);
	glColorPointer(3, GL_FLOAT, sizeof(vector3d), &colorCesped[0]);

	glDrawArrays(GL_TRIANGLES, 0, cesped.size());

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
}
