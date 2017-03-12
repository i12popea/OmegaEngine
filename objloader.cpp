#include "objloader.hpp"

using namespace std;
using namespace ed;

namespace ed
{

Material& Material::operator = (const Material &m)
{
	if(this != &m)
	{
		setNombre(m.getNombre());
		setAlpha(m.getAlpha());
		setNs(m.getNs());
		setDif(m.getDif());
		setAmb(m.getAmb());
		setSpec(m.getSpec());
		setIllum(m.getIllum());
		setIdTextura(m.getIdTextura());
	}
	return *this;
}

Objeto& Objeto::operator = (const Objeto &o)
{
	if(this != &o)
	{
	//	_banderaAnimacion = o._banderaAnimacion;
		setMaterial(o.getMaterial());
		setNombreMaterial(o.getNombreMaterial());
		setIndiceMaterial(o.getIndiceMaterial());
	//	_animacion = o._animacion;
		_lista_vertices = o._lista_vertices;
		_lista_normales = o._lista_normales;
		_lista_coordenadas = o._lista_coordenadas;
		_lista_colores = o._lista_colores;
		_matrizCoordenadas = o._matrizCoordenadas;
		_matrizVertices = o._matrizVertices;
		_matrizNormales = o._matrizNormales;
		_matrizColores = o._matrizColores;
		_indicePlano = o._indicePlano;
		_indiceNombre = o._indiceNombre;
	}
	return *this;
}

void Objeto::PrepararShader(Shader &shader, int textura, GLfloat LightPosition[], GLfloat LightColor[], int CantidadLuces)
{
	int Cantidad = glGetUniformLocation(shader.id(), "NumLights");
	glUniform1i(Cantidad, CantidadLuces);

	int LightVector = glGetUniformLocation(shader.id(), "eyeSpaceLightVector");
	glUniform3fv(LightVector, CantidadLuces, LightPosition);

	int LightColors = glGetUniformLocation(shader.id(), "diffuseColor");
	glUniform4fv(LightColors, 1, LightColor);

	int texture_location = glGetUniformLocation(shader.id(), "texture_color");
	glUniform1i(texture_location, textura);
}

void Objeto::CargaOBJ(string archivo)
{
	bool caraSimple = false, caraTextura = false, MTLabierto = false;
	vector<unsigned int> verticeIndice, uvIndice, normalIndice;
	vector<vector3d> temp_vertice, temp_normal, vertices, normales;
	vector<vector2d> temp_uv, coordenadas;
	vector<IndicePlano> planos, planoCoordenadas, planoNormales;

	vector<string> temp_nombreUSEMTL;
	vector<int> temp_indiceNombre, temp_indicePlano;
	ifstream in(archivo.c_str(), ios::in);
	if(!in)
	{
		cerr << "No se puede abrir " << archivo << endl;
		exit(1);
	}

	string line;
	//vector<Weight> vectorWeight;
	vector<vector2d> vectorCoord;

	while (getline(in, line))
	{
		/*if(line.substr(0,10) == "animacion ")
		{
			string ficheroanimacion(line.substr(10)); Animacion animacion;
			if(!animacion.ReadMD5Anim(ficheroanimacion))
				cout << "Fallo en la carga del fichero de animaciones\n";
			else
			{
				_animacion = animacion;
				_banderaAnimacion = true;
			}
		}*/
		if(line.substr(0,2) == "v ")
		{
			istringstream s(line.substr(2));
			float x, y, z;
			vector3d v; s >> x; s >> y; s >> z;
			v.setX(x); v.setY(y); v.setZ(z);
			vertices.push_back(v);
		}
		else if(strcmp(line.substr(0,3).c_str(), "vn ") == 0)
		{
			istringstream s(line.substr(3));
			float x, y, z;
			vector3d v; s >> x; s >> y; s >> z;
			v.setX(x); v.setY(y); v.setZ(z);
			normales.push_back(v);
		}
		else if(line.substr(0,2) == "f ")
		{
			istringstream s(line.substr(2));
			string delim1 = "//  ";
			string delim2 = "//";
			vector<float> contenidoResultado;
			string contenido = line.substr(2);

			contenidoResultado = vectorDeCadena(contenido, delim1);
			if(contenidoResultado.size() == 3)	//Logitud del vector: 3;
			{
				caraSimple = true;
				GLushort a,b,c;
				a = contenidoResultado[0]; b = contenidoResultado[1]; c = contenidoResultado[2];
				a--; b--; c--;
				IndicePlano plano; plano.setPuntoA(a); plano.setPuntoB(b); plano.setPuntoC(c);
				planos.push_back(plano);
			}
			if(contenidoResultado.size() == 6)	//Logitud del vector: 6;
			{
				GLushort a,b,c;
				a = contenidoResultado[0]; b = contenidoResultado[2]; c = contenidoResultado[4];
				a--; b--; c--;
				IndicePlano plano; plano.setPuntoA(a); plano.setPuntoB(b); plano.setPuntoC(c);
				planos.push_back(plano);

				if(contenido.find(delim2) != string::npos) //Tiene vectores y normales
				{
					//caraNormal = true;
					a = contenidoResultado[1]; b = contenidoResultado[3]; c = contenidoResultado[5];
					a--; b--; c--;
					plano.setPuntoA(a); plano.setPuntoB(b); plano.setPuntoC(c);
					planoNormales.push_back(plano);
				}
				else //Tiene vectores y texturas
				{
					caraTextura = true;
					a = contenidoResultado[1]; b = contenidoResultado[3]; c = contenidoResultado[5];
					a--; b--; c--;
					plano.setPuntoA(a); plano.setPuntoB(b); plano.setPuntoC(c);
					planoCoordenadas.push_back(plano);
				}
			}
			if(contenidoResultado.size() == 9)	//Logitud del vector: 9;
			{
				GLushort a,b,c;
				a = contenidoResultado[0]; b = contenidoResultado[3]; c = contenidoResultado[6];

				a--; b--; c--;
				IndicePlano plano; plano.setPuntoA(a); plano.setPuntoB(b); plano.setPuntoC(c);
				planos.push_back(plano);

				a = contenidoResultado[1]; b = contenidoResultado[4]; c = contenidoResultado[7];
				a--; b--; c--;
				plano.setPuntoA(a); plano.setPuntoB(b); plano.setPuntoC(c);
				planoCoordenadas.push_back(plano);

				a = contenidoResultado[2]; b = contenidoResultado[5]; c = contenidoResultado[8];
				a--; b--; c--;
				plano.setPuntoA(a); plano.setPuntoB(b); plano.setPuntoC(c);
				planoNormales.push_back(plano);
			}
		}
		else if(strcmp(line.substr(0,3).c_str(), "vt ") == 0)
		{
			istringstream s(line.substr(3));
			float x, y;
			vector2d v; s >> x; s >> y;
			v.setU(x); v.setV(y);
			coordenadas.push_back(v);
		}
		else if(strcmp(line.substr(0,7).c_str(), "mtllib ") == 0)
		{
			string ficheromtl(line.substr(7));
			MTLabierto = CargaMTL(ficheromtl);
		}
		else if(strcmp(line.substr(0,7).c_str(), "usemtl ") == 0)
		{
			string nombreUseMLT(line.substr(7));
			// Intentar crear vectores en el que se tengan tantos nombres e indices plano como caras tenga para indexarlos con las texturas
			temp_nombreUSEMTL.push_back(nombreUseMLT);
			temp_indicePlano.push_back(planos.size());
		}
		else if (line[0] == '#') { /* ignorar esta linea */ }
		else { /* ignorar esta linea */ }
	}

	//Pasamos los nombres al indice que le corresponde
	if(MTLabierto == true) // Modificar??
		CrearIndices(temp_nombreUSEMTL, temp_indiceNombre, temp_indicePlano, planos);
	//Fin de indexación de elementos

	if((caraSimple == true) || (caraTextura == true))
		CrearVectorNormal(vertices, normales, planos, planoNormales);

	in.close();

	CrearListas(temp_indiceNombre, temp_indicePlano, vertices, normales, coordenadas, planos, planoNormales, planoCoordenadas);

	if(_indicePlano.size() > 0)
		CrearMatricesElementos();
}

void Objeto::CrearIndices(vector<string> &temp_nombreUSEMTL, vector<int> &temp_indiceNombre, vector<int> &temp_indicePlano, vector<IndicePlano> planos)
{
	//En esta parte se intenta averiguar el indice de los materiales comparando los nombres obtenidos con los del archivo MTL
	unsigned int index;
	for(unsigned int i = 0; i < temp_nombreUSEMTL.size(); i++)
	{
		index = 0;
		while(temp_nombreUSEMTL[i] != _material[index].getNombre() && index < _material.size() - 1){
			index++;
		}
		temp_indiceNombre.push_back(index);
	}

	//Indexación de elementos
	vector<int> aux;
	for(unsigned int i = 0; i < temp_indiceNombre.size(); i++) //Indice de nombre de materiales para los indices de texturas
	{
		if(i < temp_indiceNombre.size() - 1) //Se registrarán los valores de los indices de las caras para el material antes del final
		{
			for(int j = temp_indicePlano[i]; j < temp_indicePlano[i + 1]; j++)
			{
				_indiceMaterial.push_back(temp_indiceNombre[i]);
			}
			aux = _indiceMaterial;
		}
		if(i == temp_indiceNombre.size() - 1) //Se registrará la última posición
		{
			for(unsigned int j = temp_indicePlano[i]; j < planos.size(); j++)
			{
				_indiceMaterial.push_back(temp_indiceNombre[i]); //Registrará el último indice de nombres de materiales
			}
		}
	}
}

void Objeto::CrearListas(vector<int> temp_indiceNombre, vector<int> temp_indicePlano, vector<vector3d> vertices, vector<vector3d> normales, vector<vector2d> coordenadas, vector<IndicePlano> planos, vector<IndicePlano> planoNormales, vector<IndicePlano> planoCoordenadas)
{
	// Los pasamos a listas
	for(unsigned int indice=0; indice < planos.size(); indice++)
	{
		if(_material.size() > 0)
		{
			vector3d color(_material[_indiceMaterial[indice]].getDif(0), _material[_indiceMaterial[indice]].getDif(1), _material[_indiceMaterial[indice]].getDif(2));
			_lista_colores.push_back(color);
			_lista_colores.push_back(color);
			_lista_colores.push_back(color);
		}

		//Primer vertice
		vector3d normalA(normales[planoNormales[indice].getPuntoA()].getX(), normales[planoNormales[indice].getPuntoA()].getY(), normales[planoNormales[indice].getPuntoA()].getZ());
		_lista_normales.push_back(normalA);
		if(coordenadas.size() > 0)
		{
			vector2d coordenadaA(coordenadas[planoCoordenadas[indice].getPuntoA()].getU(), coordenadas[planoCoordenadas[indice].getPuntoA()].getV());
			_lista_coordenadas.push_back(coordenadaA);
		}
		vector3d verticeA( vertices[ planos[indice].getPuntoA() ].getX(), vertices[ planos[indice].getPuntoA() ].getY(), vertices[ planos[indice].getPuntoA() ].getZ());
		_lista_vertices.push_back(verticeA);

		//Segundo vertice
		vector3d normalB(normales[planoNormales[indice].getPuntoB()].getX(), normales[planoNormales[indice].getPuntoB()].getY(), normales[planoNormales[indice].getPuntoB()].getZ());
		_lista_normales.push_back(normalB);
		if(coordenadas.size() > 0)
		{
			vector2d coordenadaB(coordenadas[planoCoordenadas[indice].getPuntoB()].getU(), coordenadas[planoCoordenadas[indice].getPuntoB()].getV());
			_lista_coordenadas.push_back(coordenadaB);
		}
		vector3d verticeB( vertices[ planos[indice].getPuntoB() ].getX(), vertices[ planos[indice].getPuntoB() ].getY(), vertices[ planos[indice].getPuntoB() ].getZ());
		_lista_vertices.push_back(verticeB);

		//Tercer vertice
		vector3d normalC(normales[planoNormales[indice].getPuntoC()].getX(), normales[planoNormales[indice].getPuntoC()].getY(), normales[planoNormales[indice].getPuntoC()].getZ());
		_lista_normales.push_back(normalC);
		if(coordenadas.size() > 0)
		{
			vector2d coordenadaC(coordenadas[planoCoordenadas[indice].getPuntoC()].getU(), coordenadas[planoCoordenadas[indice].getPuntoC()].getV());
			_lista_coordenadas.push_back(coordenadaC);
		}
		vector3d verticeC( vertices[ planos[indice].getPuntoC() ].getX(), vertices[ planos[indice].getPuntoC() ].getY(), vertices[ planos[indice].getPuntoC() ].getZ());
		_lista_vertices.push_back(verticeC);
	}

	//Guardamos los indices para las texturas y las divisiones de los vectores
	_indicePlano = temp_indicePlano;
	_indiceNombre = temp_indiceNombre;
}

void Objeto::CrearMatricesElementos()
{
	//Empezamos con las divisiones de los vectores
	vector<vector3d>::iterator iteradorVertices = _lista_vertices.begin();
	vector<vector2d>::iterator iteradorCoords = _lista_coordenadas.begin();
	vector<vector3d>::iterator iteradorNormales = _lista_normales.begin();
	vector<vector3d>::iterator iteradorColores = _lista_colores.begin();
	for(unsigned int i = 0; i < _indicePlano.size(); i++)
	{
		if(i < _indicePlano.size() - 1)
		{
			_matrizVertices.push_back(vector<vector3d>());
			_matrizVertices[_matrizVertices.size() - 1] = vector<vector3d>(iteradorVertices + _indicePlano[i]*3, iteradorVertices + _indicePlano[i + 1]*3);
			if(_lista_coordenadas.size() > 0)
			{
				_matrizCoordenadas.push_back(vector<vector2d>());
				_matrizCoordenadas[_matrizCoordenadas.size() - 1] = vector<vector2d>(iteradorCoords + _indicePlano[i]*3, iteradorCoords + _indicePlano[i + 1]*3);
			}
			_matrizNormales.push_back(vector<vector3d>());
			_matrizNormales[_matrizNormales.size() - 1] = vector<vector3d>(iteradorNormales + _indicePlano[i]*3, iteradorNormales + _indicePlano[i + 1]*3);
			if(_lista_colores.size() > 0)
			{
				_matrizColores.push_back(vector<vector3d>());
				_matrizColores[_matrizColores.size() - 1] = vector<vector3d>(iteradorColores + _indicePlano[i]*3, iteradorColores + _indicePlano[i + 1]*3);
			}
		}
		if(i == _indicePlano.size() - 1)
		{
			_matrizVertices.push_back(vector<vector3d>());
			_matrizVertices[_matrizVertices.size() - 1] = vector<vector3d>(iteradorVertices + _indicePlano[i]*3, iteradorVertices + _lista_vertices.size());
			if(_lista_coordenadas.size() > 0)
			{
				_matrizCoordenadas.push_back(vector<vector2d>());
				_matrizCoordenadas[_matrizCoordenadas.size() - 1] = vector<vector2d>(iteradorCoords + _indicePlano[i]*3, iteradorCoords + _lista_coordenadas.size());
			}
			_matrizNormales.push_back(vector<vector3d>());
			_matrizNormales[_matrizNormales.size() - 1] = vector<vector3d>(iteradorNormales + _indicePlano[i]*3, iteradorNormales + _lista_normales.size());
			if(_lista_colores.size() > 0)
			{
				_matrizColores.push_back(vector<vector3d>());
				_matrizColores[_matrizColores.size() - 1] = vector<vector3d>(iteradorColores + _indicePlano[i]*3, iteradorColores + _lista_colores.size());
			}
		}
	}
}

void Objeto::CrearVectorNormal(vector<vector3d> vertices, vector<vector3d> &normales, vector<IndicePlano> &planos, vector<IndicePlano> &planoNormales)
{
	vector<int> visto;
	normales.resize(vertices.size(), vector3d(0.0, 0.0, 0.0));
	visto.resize(vertices.size(), 0);
	for (unsigned int i = 0; i < planos.size(); i++)
	{
		GLushort ia = planos[i].getPuntoA(), ib = planos[i].getPuntoB(), ic = planos[i].getPuntoC();

		vector3d normal = normalizarVector(productoVectorial(vertices[ib] - vertices[ia], vertices[ic] - vertices[ia]));

		int v[3];  v[0] = ia;  v[1] = ib;  v[2] = ic;
		for (int j = 0; j < 3; j++)
		{
			GLushort actual = v[j];
			visto[actual]++;
			if (visto[actual] == 1)
				normales[actual] = normal;
			else
			{
				normales[actual].setX(normales[actual].getX() * (1.0 - 1.0/visto[actual]) + normal.getX() * 1.0/visto[actual]);
				normales[actual].setY(normales[actual].getY() * (1.0 - 1.0/visto[actual]) + normal.getY() * 1.0/visto[actual]);
				normales[actual].setZ(normales[actual].getZ() * (1.0 - 1.0/visto[actual]) + normal.getZ() * 1.0/visto[actual]);
				normales[actual] = normalizarVector(normales[actual]);
			}
		}
	}
	planoNormales = planos;
}

bool Objeto::CargaMTL(string archivo)
{
	ifstream mtl(archivo.c_str(), ios::in);
	if(!mtl)
	{
		cerr << "No se puede abrir " << archivo << endl;
		return false;
	}

	string nuevaLinea, imagen, nombre1;
	vector< vector<string> > contenidoLinea;
	float alpha1, ns1;
	vector< vector<float> > dif, amb, spec; //Matriz para guardar dif, amb y spec (hay que respetar los espacios)
	int illum1, id_textura1 = -1;
	while (getline(mtl, nuevaLinea))
	{
		if(nuevaLinea.substr(0,7) == "newmtl ")
		{
			contenidoLinea.push_back(vector<string>()); //Añadimos un vector de string
			contenidoLinea[contenidoLinea.size() - 1].push_back(nuevaLinea);
		}
		if(nuevaLinea.substr(0,3) == "Ka ")
			contenidoLinea[contenidoLinea.size() - 1].push_back(nuevaLinea);
		if(nuevaLinea.substr(0,3) == "Kd ")
			contenidoLinea[contenidoLinea.size() - 1].push_back(nuevaLinea);
		if(nuevaLinea.substr(0,3) == "Ks ")
			contenidoLinea[contenidoLinea.size() - 1].push_back(nuevaLinea);
		if(nuevaLinea.substr(0,2) == "d ")
			contenidoLinea[contenidoLinea.size() - 1].push_back(nuevaLinea);
		if(nuevaLinea.substr(0,3) == "Ns ")
			contenidoLinea[contenidoLinea.size() - 1].push_back(nuevaLinea);
		if(nuevaLinea.substr(0,6) == "illum ")
			contenidoLinea[contenidoLinea.size() - 1].push_back(nuevaLinea);
		if(nuevaLinea.substr(0,7) == "map_Kd ")
			contenidoLinea[contenidoLinea.size() - 1].push_back(nuevaLinea);
	}

	for(unsigned int i = 0; i < contenidoLinea.size(); i++)
	{
		for(unsigned int j = 0; j < contenidoLinea[i].size(); j++)
		{
			if(contenidoLinea[i][j].substr(0,7) == "newmtl ")
			{
				nombre1 = contenidoLinea[i][j].substr(7);
			}
			if(contenidoLinea[i][j].substr(0,3) == "Ka ")
			{
				float a, b, c;
				istringstream s(contenidoLinea[i][j].substr(3));
				s >> a; s >> b; s >> c;
				amb.push_back(vector<float>()); //Añadimos un vector de float
				amb[amb.size() - 1].push_back(a); amb[amb.size() - 1].push_back(b); amb[amb.size() - 1].push_back(c); //Añadimos en la última fila los elementos
			}
			if(contenidoLinea[i][j].substr(0,3) == "Kd ")
			{
				float a, b, c;
				istringstream s(contenidoLinea[i][j].substr(3));
				s >> a; s >> b; s >> c;
				dif.push_back(vector<float>());
				dif[dif.size() - 1].push_back(a); dif[dif.size() - 1].push_back(b); dif[dif.size() - 1].push_back(c);
			}
			if(contenidoLinea[i][j].substr(0,3) == "Ks ")
			{
				float a, b, c;
				istringstream s(contenidoLinea[i][j].substr(3));
				s >> a; s >> b; s >> c;
				spec.push_back(vector<float>());
				spec[spec.size() - 1].push_back(a); spec[spec.size() - 1].push_back(b); spec[spec.size() - 1].push_back(c);
			}
			if(contenidoLinea[i][j].substr(0,2) == "d ")
			{
				istringstream s(contenidoLinea[i][j].substr(2));
				s >> alpha1;
			}
			if(contenidoLinea[i][j].substr(0,3) == "Ns ")
			{
				istringstream s(contenidoLinea[i][j].substr(3));
				s >> ns1;
			}
			if(contenidoLinea[i][j].substr(0,6) == "illum ")
			{
				istringstream s(contenidoLinea[i][j].substr(6));
				s >> illum1;
			}
			if(contenidoLinea[i][j].substr(0,7) == "map_Kd ")
			{
				imagen = contenidoLinea[i][j].substr(7);
				id_textura1 = LoadBitmap(imagen);
			}
		}
		Material material(nombre1, alpha1, ns1, dif[i], amb[i], spec[i], illum1, id_textura1);
		_material.push_back(material);
		//Valores por defecto por si no se encontran en el fichero
		alpha1 = 1.0;
		illum1 = 1.0;
		id_textura1 = -1;
	}

	mtl.close();
	return true;
}

void Objeto::dibujar(Shader &shader, GLfloat LightPosition[], GLfloat LightColor[], int CantidadLuces)
{
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	if(_material.size() > 0)
	{
//shader.bind();
		for(unsigned int i = 0; i < _indicePlano.size(); i++)
		{
shader.bind();
			//Principio del tratamiento de iluminacion
			float diffuse[]={_material[_indiceMaterial[i]].getDif(0),_material[_indiceMaterial[i]].getDif(1), _material[_indiceMaterial[i]].getDif(2), 1};
			float ambient[]={_material[_indiceMaterial[i]].getAmb(0), _material[_indiceMaterial[i]].getAmb(1), _material[_indiceMaterial[i]].getAmb(2), 1};
			float specular[]={_material[_indiceMaterial[i]].getSpec(0), _material[_indiceMaterial[i]].getSpec(1), _material[_indiceMaterial[i]].getSpec(2), 1};
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialf(GL_FRONT, GL_SHININESS, _material[_indiceMaterial[i]].getNs());
			//Final del tratamiento de iluminacion

			PrepararShader(shader, _material[_indiceNombre[i]].getIdTextura(), LightPosition, LightColor, CantidadLuces);

/*GLfloat Position[] = {0, 0, 0};
GLfloat Color[] = {1, 1, 1, 0};

int Cantidad = glGetUniformLocation(shader.id(), "NumLights");
glUniform1i(Cantidad, 1);

int LightVector = glGetUniformLocation(shader.id(), "eyeSpaceLightVector");
glUniform3fv(LightVector, 1, Position);

int LightColors = glGetUniformLocation(shader.id(), "diffuseColor");
glUniform4fv(LightColors, 1, Color);

int texture_location = glGetUniformLocation(shader.id(), "texture_color");
glUniform1i(texture_location,  _material[_indiceNombre[i]].getIdTextura());*/

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, sizeof(vector3d), &_matrizVertices[i][0]);

			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, sizeof(vector3d), &_matrizNormales[i][0]);

			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(3, GL_FLOAT, sizeof(vector3d), &_matrizColores[i][0]);

			glClientActiveTexture(GL_TEXTURE0);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindTexture(GL_TEXTURE_2D, _material[_indiceNombre[i]].getIdTextura());
			glTexCoordPointer(2, GL_FLOAT, sizeof(vector2d), &_matrizCoordenadas[i][0]);

			glDrawArrays(GL_TRIANGLES, 0, _matrizVertices[i].size()); // 3 x número de caras

			glDisableClientState(GL_TEXTURE_COORD_ARRAY);  // disable vertex arrays
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
shader.unbind();
		}
//shader.unbind();
	}
	glDisable(GL_TEXTURE_2D);

	if(_material.size() == 0) //Si no hay ningún archivo MTL vinculado al fichero OBJ
	{
		PrepararShader(shader, -1, LightPosition, LightColor, CantidadLuces);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glVertexPointer(3, GL_FLOAT, sizeof(vector3d), &_lista_vertices[0]);
		glNormalPointer(GL_FLOAT, sizeof(vector3d), &_lista_normales[0]);

		glDrawArrays(GL_TRIANGLES, 0, _lista_vertices.size()); // 3 x número de caras

		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	glPopMatrix();
}

void Objeto::dibujar()
{
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	if(_material.size() > 0)
	{
		for(unsigned int i = 0; i < _indicePlano.size(); i++)
		{
			//Principio del tratamiento de iluminacion
			float diffuse[]={_material[_indiceMaterial[i]].getDif(0),_material[_indiceMaterial[i]].getDif(1), _material[_indiceMaterial[i]].getDif(2), 1};
			float ambient[]={_material[_indiceMaterial[i]].getAmb(0), _material[_indiceMaterial[i]].getAmb(1), _material[_indiceMaterial[i]].getAmb(2), 1};
			float specular[]={_material[_indiceMaterial[i]].getSpec(0), _material[_indiceMaterial[i]].getSpec(1), _material[_indiceMaterial[i]].getSpec(2), 1};
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialf(GL_FRONT, GL_SHININESS, _material[_indiceMaterial[i]].getNs());
			//Final del tratamiento de iluminacion

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, sizeof(vector3d), &_matrizVertices[i][0]);

			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, sizeof(vector3d), &_matrizNormales[i][0]);

			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(3, GL_FLOAT, sizeof(vector3d), &_matrizColores[i][0]);

			glClientActiveTexture(GL_TEXTURE0);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindTexture(GL_TEXTURE_2D, _material[_indiceNombre[i]].getIdTextura());
			glTexCoordPointer(2, GL_FLOAT, sizeof(vector2d), &_matrizCoordenadas[i][0]);

			glDrawArrays(GL_TRIANGLES, 0, _matrizVertices[i].size()); // 3 x número de caras

			glDisableClientState(GL_TEXTURE_COORD_ARRAY);  // disable vertex arrays
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
		}
	}
	glDisable(GL_TEXTURE_2D);

	if(_material.size() == 0) //Si no hay ningún archivo MTL vinculado al fichero OBJ
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glVertexPointer(3, GL_FLOAT, sizeof(vector3d), &_lista_vertices[0]);
		glNormalPointer(GL_FLOAT, sizeof(vector3d), &_lista_normales[0]);

		glDrawArrays(GL_TRIANGLES, 0, _lista_vertices.size()); // 3 x número de caras

		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	glPopMatrix();
}

/*void Objeto::ProcesarModelo(vector<vector3d> &mesh, vector<vector2d> &meshCoord, vector<vector3d> &meshNormal, const vector<skeletonJoint> &skeleton, vector<Weight> weights, vector<vector2d> coordAnim, vector<int> starts, vector<int> counts, vector<int> indiceVertices)
{
	vector<vector3d> vectorVertices, verticesTraducidos, normalesTraducidos;
	vector<vector2d> texturasTraducidas;
	float radian = 3.1415926535897932/180;
	float posRotY, posRotZ;
	for(unsigned int i = 0; i < starts.size(); i++)
	{
		vector3d finalPos(0, 0, 0);
		int &start = starts[i];
		for(int j = 0; j < counts[i]; j++)
		{
			Weight &weight = weights[start + j];
			skeletonJoint joint = skeleton[weight.getJoint()];

			vector3d rotPos;
			rotPos = Quat_rotatePoint (joint.getOrientacion(), weight.getPosicion());

			finalPos = finalPos + ( joint.getPosicion() + rotPos ) * weight.getBias();
		}
		posRotY = finalPos.getY()*cos(-90*radian) - finalPos.getZ()*sin(-90*radian);
		posRotZ = finalPos.getY()*sin(-90*radian) + finalPos.getZ()*cos(-90*radian);
		finalPos.setY(posRotY);
		finalPos.setZ(posRotZ);
		vectorVertices.push_back(finalPos);
	}

	for (unsigned int i = 0; i < indiceVertices.size(); i = i + 3)
	{
		verticesTraducidos.push_back(vectorVertices[indiceVertices[i]]); verticesTraducidos.push_back(vectorVertices[indiceVertices[i + 1]]); verticesTraducidos.push_back(vectorVertices[indiceVertices[i + 2]]);
		texturasTraducidas.push_back(coordAnim[indiceVertices[i]]); texturasTraducidas.push_back(coordAnim[indiceVertices[i + 1]]); texturasTraducidas.push_back(coordAnim[indiceVertices[i + 2]]);
		vector3d normal = normalizarVector(productoVectorial(verticesTraducidos[i + 1] - verticesTraducidos[i], verticesTraducidos[i + 2] - verticesTraducidos[i]));
		normalesTraducidos.push_back(normal); normalesTraducidos.push_back(normal); normalesTraducidos.push_back(normal);
	}
	mesh = verticesTraducidos;
	meshCoord = texturasTraducidas;
	meshNormal = normalesTraducidos;
}

void Objeto::Actualizar(float tiempo)
{
	_animacion.Animate(tiempo);
	const vector<skeletonJoint> frameSkeleton = _animacion.getAnimSkeleton();

	for(unsigned int i = 0; i < _matrizVertices.size(); i++)
		ProcesarModelo(_matrizVertices[i], _matrizCoordenadas[i], _matrizNormales[i], frameSkeleton, _animacion.getVectorWeight(i), _animacion.getVectorCoordAnim(i), _animacion.getVectorStart(i), _animacion.getVectorCount(i), _animacion.getVectorIndiceVertices(i));
}*/

vector<float> vectorDeCadena(string cadena, string delimitador)
{
	vector<float> lista;
	char * punteroContenido;
	punteroContenido = strtok(&cadena[0], &delimitador[0]);

	while (punteroContenido != NULL)
	{
		float temporal = atof(punteroContenido);
		lista.push_back(temporal);
		punteroContenido = strtok(NULL, &delimitador[0]);
	}

	return lista;
}

}
