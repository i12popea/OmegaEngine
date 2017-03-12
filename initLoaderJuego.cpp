#include "initLoaderJuego.hpp"

using namespace std;
using namespace ed;

bool avanzar = false, retroceder = false, derecha = false, izquierda = false, agachado = false;
//int shift = 0;
int frameCount = 0;
float currentTime = 0, previousTime = 0, fps = 0;
/*Shader shader1, shader2;
GLfloat Position[] = {-6, 1, 1}; //GLfloat Position[] = {0, -5.5, 0};
GLfloat Color[] = {1, 0, 0, 0};
Objeto objeto;*/

namespace ed{

ConfiguracionJuego *ConfiguracionJuego::_instancia = NULL;

void ConfiguracionJuego::IniciarFramework(int argc, char *argv[])
{
	_ventana.initVentana();
	glutInit(&argc, argv);
	alutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(_ventana.getHeight(), _ventana.getWidth());
	glutInitWindowPosition(_ventana.getX(), _ventana.getY());
	glutCreateWindow("Demo shooter");

	glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		cout << "Soporte para OpenGL 2.0\n";
	else {
		cout << "OpenGL 2.0 no soportado\n";
		exit(1);
	}

	if(_ventana.getFullscreen())
		glutFullScreen();

	init();

	glutDisplayFunc(displayCallBack);
	glutIdleFunc(redibujarCallBack);
	glutReshapeFunc(reshapeCallBack);

	glutMouseFunc(ratonCallBack);
	glutPassiveMotionFunc(movimientoCallBack); //check for mouse movement
	glutMotionFunc(movimientoCallBack); //check for mouse movement

	glutKeyboardFunc(keyboardCallBack);
	glutKeyboardUpFunc(keyboardUpCallBack);
	//glutSpecialFunc(keyboardSpecial);
	glutMainLoop();
	alutExit();
}

void ConfiguracionJuego::contadorFPS()
{
	//Increase frame count
	frameCount++;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int timeInterval = currentTime - previousTime;
	if(timeInterval > 1000)
	{
		//calculate the number of frames per second
		fps = frameCount / (timeInterval / 1000.0f);
		//Set time
		previousTime = currentTime;
		//Reset frame count
		frameCount = 0;
	}
}

void ConfiguracionJuego::dibujarContadorFPS()
{
	//Una vez hecha la parte 3D pasamos a hacer la 2D: opengl 2d text in 3d space: https://stackoverflow.com/questions/18847109/displaying-fixed-location-2d-text-in-a-3d-opengl-world-using-glut
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, _ventana.getHeight(), 0.0, _ventana.getWidth());
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	ostringstream ss;
	ss << fps;
	string s("FPS: " + ss.str());

	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_LIGHTING);
	glRasterPos3f(20, 560, 0);
	for (unsigned int i=0; i<strlen(s.c_str()); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
	glEnable(GL_LIGHTING);


	ostringstream getPosicion;
	getPosicion << _jugador.getCamara()->getVector().getX();
	string posX(getPosicion.str()); getPosicion.str(""); getPosicion.clear();
	getPosicion << _jugador.getCamara()->getVector().getY();
	string posY(getPosicion.str()); getPosicion.str(""); getPosicion.clear();
	getPosicion << _jugador.getCamara()->getVector().getZ();
	string posZ(getPosicion.str());
	string posicion = posX + ' ' + posY + ' ' + posZ;

	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_LIGHTING);
	glRasterPos3f(520, 560, 0);
	for (unsigned int i = 0; i<strlen(posicion.c_str()); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, posicion[i]);
	glEnable(GL_LIGHTING);

	/*ostringstream getShift;
	getShift << shift;
	string tecla(getShift.str());

	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_LIGHTING);
	glRasterPos3f(520, 540, 0);
	for (unsigned int i = 0; i<strlen(tecla.c_str()); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, tecla[i]);
	glEnable(GL_LIGHTING);*/

	//Y volvemos a hacerlo 3D
	/*glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();*/
	glPopMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void ConfiguracionJuego::dibujarHUD()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, _ventana.getHeight(), 0.0, _ventana.getWidth());
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	ostringstream getSalud;
	getSalud << _jugador.getSalud();
	string salud(getSalud.str());

	/*ostringstream getArma;
	getArma << _jugador.getArma()->getMunicionDisparada()->size();
	string arma(getArma.str());*/

	ostringstream getMunicion;
	getMunicion << _jugador.getArma()->getMunicion();
	string municion(getMunicion.str());

	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(20, 20, 0);
	for (unsigned int i=0; i<strlen(salud.c_str()); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, salud[i]);
	glEnable(GL_LIGHTING);

	/*glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(90, 20, 0);
	for (unsigned int i=0; i<strlen(arma.c_str()); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, arma[i]);
	glEnable(GL_LIGHTING);*/

	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(640, 20, 0);
	for (unsigned int i=0; i<strlen(municion.c_str()); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, municion[i]);
	glEnable(GL_LIGHTING);

	//Y volvemos a hacerlo 3D
	glPopMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void ConfiguracionJuego::display()
{
	initMouse();
	glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	movimientoJugador();
	_jugador.getCamara()->camara();

/*shader1.bind();
//int Cantidad = glGetUniformLocation(_shader[2].id(), "NumLights");
//glUniform1i(Cantidad, 1);

int LightVector = glGetUniformLocation(shader1.id(), "eyeSpaceLightVector");
glUniform3fv(LightVector, 1, Position);

int LightColors = glGetUniformLocation(shader1.id(), "diffuseColor");
glUniform4fv(LightColors, 1, Color);

glPushMatrix();
glTranslatef(0, -5.5, 0);
glutSolidTeapot(4);
glPopMatrix();
shader1.unbind();*/

/*shader2.bind();
int Cantidad = glGetUniformLocation(shader2.id(), "NumLights");
glUniform1i(Cantidad, 1);

int LightVector = glGetUniformLocation(shader2.id(), "eyeSpaceLightVector");
glUniform3fv(LightVector, 1, Position);

int LightColors = glGetUniformLocation(shader2.id(), "diffuseColor");
glUniform4fv(LightColors, 1, Color);

int texture_location = glGetUniformLocation(shader2.id(), "texture_color");
glUniform1i(texture_location,  objeto.getMaterial()[0].getIdTextura());

glPushMatrix();
glTranslatef(0, -5.5, 0);
objeto.dibujar();
glPopMatrix();
shader2.unbind();*/

/*glPushMatrix();
glTranslatef(0, 0, 0);
//objeto.dibujar(shader2, Position, Color, 1);
objeto.dibujar(_shader[5], _luces.getLightPosition(), _luces.getLightColor(), _luces.getCantidadFocos());
glPopMatrix();*/

	_frustum.ExtraerFrustum();

	//_jugador.ColisionPersonaje(_escenario.getListaVertices(), _objetoColision, _colisionOctree);
	_jugador.ColisionPersonaje(_colisionBox, _colisionSphere, _colisionOctree, _tipoObjeto, _objeto, _posicion, _grados, _rotacion, _escalado);
	_jugador.MostrarArma();

	RenderizarCesped(_cesped, _colorCesped);

	for(unsigned int i = 0; i < _enemigos.size(); i++)
	{
		glPushMatrix();
		glTranslatef(_enemigos[i].getVector3d().getX(), _enemigos[i].getVector3d().getY(), _enemigos[i].getVector3d().getZ());
		glutSolidCube(1);
		glPopMatrix();
		_enemigos[i].ColisionEnemigo(_colisionBox, _colisionSphere, _colisionOctree);
		_enemigos[i].ActualizarEstado();
	}

	if(_cielo.size() > 0)
		if(_existeCielo)
		{
			glPushMatrix();
			glTranslatef(_posicionCielo.getX(), _posicionCielo.getY(), _posicionCielo.getZ());
			Skybox(_cielo, _tamanoSkybox);
			glPopMatrix();
		}

	_jugador.ObtenerAngulos();

	// Comprobacion del Frustum Culling
	for(unsigned int i = 0; i < _colisionBox.size(); i++)
	{
		vector3d centro(_colisionBox[i].getVector3d());
		if(_frustum.CubeInFrustum(centro, _colisionBox[i].getAlto(), _colisionBox[i].getLargo(), _colisionBox[i].getAncho()))
		{
			glPushMatrix();
			glTranslatef(_posicion[i].getX(), _posicion[i].getY(), _posicion[i].getZ());
			glRotatef(_grados[i], _rotacion[i].getX(), _rotacion[i].getY(), _rotacion[i].getZ());
			glScalef(_escalado[i].getX(), _escalado[i].getY(), _escalado[i].getZ());
			_objeto[i].dibujar(_shader[5], _luces.getLightPosition(), _luces.getLightColor(), _luces.getCantidadFocos());
			glPopMatrix();
		}
	}
	for(unsigned int i = 0; i < _colisionSphere.size(); i++)
	{
		if(_frustum.sphereInFrustum(_colisionSphere[i]))
		{
			_shader[5].bind();
			glPushMatrix();
			glTranslatef(_posicion[_colisionBox.size() + i].getX(), _posicion[_colisionBox.size() + i].getY(), _posicion[_colisionBox.size() + i].getZ());
			glRotatef(_grados[_colisionBox.size() + i], _rotacion[_colisionBox.size() + i].getX(), _rotacion[_colisionBox.size() + i].getY(), _rotacion[_colisionBox.size() + i].getZ());
			glScalef(_escalado[_colisionBox.size() + i].getX(), _escalado[_colisionBox.size() + i].getY(), _escalado[_colisionBox.size() + i].getZ());
			_objeto[_colisionBox.size() + i].dibujar(_shader[5], _luces.getLightPosition(), _luces.getLightColor(), _luces.getCantidadFocos());
			//_objeto[_colisionBox.size() + i].dibujar();
			glPopMatrix();
			_shader[5].unbind();
		}
	}
	for(unsigned int i = 0; i < _colisionOctree.size(); i++)
	{
		vector3d centro(_colisionOctree[i]->getCentro());
		//bool resultado = true;
		//_colisionOctree[i]->FrustumOctreeOctetos(_frustum, resultado);
		//if(resultado)
		if(_frustum.CubeInFrustum(centro, _colisionOctree[i]->getTamano().getY(), _colisionOctree[i]->getTamano().getZ(), _colisionOctree[i]->getTamano().getX()))
		//if(_colisionOctree[i]->FrustumOctreePuntos(_frustum))
		//if(_colisionOctree[i]->FrustumOctreeOctetos(_frustum))
		{
			_shader[5].unbind();
			glPushMatrix();
			glTranslatef(_posicion[_colisionBox.size() + _colisionSphere.size() + i].getX(), _posicion[_colisionBox.size() + _colisionSphere.size() + i].getY(), _posicion[_colisionBox.size() + _colisionSphere.size() + i].getZ());
			glRotatef(_grados[_colisionBox.size() + _colisionSphere.size() + i], _rotacion[_colisionBox.size() + _colisionSphere.size() + i].getX(), _rotacion[_colisionBox.size() + _colisionSphere.size() + i].getY(), _rotacion[_colisionBox.size() + _colisionSphere.size() + i].getZ());
			glScalef(_escalado[_colisionBox.size() + _colisionSphere.size() + i].getX(), _escalado[_colisionBox.size() + _colisionSphere.size() + i].getY(), _escalado[_colisionBox.size() + _colisionSphere.size() + i].getZ());
			_objeto[_colisionBox.size() + _colisionSphere.size() + i].dibujar(_shader[5], _luces.getLightPosition(), _luces.getLightColor(), _luces.getCantidadFocos());
			//_objeto[_colisionBox.size() + _colisionSphere.size() + i].dibujar();
			glPopMatrix();
			_shader[5].unbind();
		}
	}

	dibujarContadorFPS();
	dibujarHUD();

	glutSwapBuffers(); //swap the buffers
}

void ConfiguracionJuego::displayCallBack()	//Revisar
{
	_instancia->display();
}

void ConfiguracionJuego::redibujar()
{
	static double curent_time = 0;
	static double last_time = 0;

	last_time = curent_time;
	curent_time = (double)glutGet (GLUT_ELAPSED_TIME) / 1000.0;

	/*for(unsigned int i = 0; i < _objeto.size(); i++)
	{
		if(_objeto[i].getBanderaAnimacion())
			_objeto[i].Actualizar( curent_time - last_time );
	}*/
	for(unsigned int i = 0; i < _modeloMD5.size(); i++)
	{
		if(_modeloMD5[i].getBanderaAnimacion())
			_modeloMD5[i].Update( curent_time - last_time );
	}

	contadorFPS();
	glutPostRedisplay();
}

void ConfiguracionJuego::redibujarCallBack()	//Revisar
{
	_instancia->redibujar();
}

void ConfiguracionJuego::reshape(int w, int h)
{
	if(h == 0)
		h = 1;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w/h, 0.1, 1000);
	_frustum.ExtraerFrustum();
	glutSwapBuffers();
}

void ConfiguracionJuego::reshapeCallBack(int w, int h)	//Revisar
{
	_instancia->reshape(w, h);
}

void ConfiguracionJuego::keyboard(unsigned char key, int x, int y)
{
	/*float vel = 0.0;
	int mod = 0;
	mod = glutGetModifiers();*/
	if (key=='w')
	{
		/*if (mod == GLUT_ACTIVE_SHIFT) {
			vel = 1.0;
		}*/
		avanzar = true;
		//jugador.getCamara()->avanzar();
	}
	if (key=='s')
	{
		retroceder = true;
		//jugador.getCamara()->retroceder();
	}
	if (key=='d')
	{
		derecha = true;
		//jugador.getCamara()->irIzquierda();
	}
	if (key=='a')
	{
		izquierda = true;
		//jugador.getCamara()->irDerecha();
	}
	if (key=='c')
	{
		//Agacharse
		//_jugador.Agacharse();
		agachado = true;
		_jugador.setAgachado(true);
		_jugador.Agacharse();
	}
	if (key == 32)
	{
		//Saltar
		_jugador.Salto();
	}
	/*if(key == 'w' || key == 'a' || key == 's' || key == 'd')
	{
		//int modifiers = glutGetModifiers(); //Para averiguar si las teclas Ctrl, Alt y Shift han sido presionadas
		//if(modifiers && GLUT_ACTIVE_SHIFT)
		if(glutGetModifiers() == GLUT_ACTIVE_SHIFT)
		{
			jugador.setVelocidadJugador(0.5);
			jugador.getCamara()->setVelocidadMovimiento(0.5);
			cout << "shift activado\n";
		}
		else
		{
			jugador.setVelocidadJugador(0.25);
			jugador.getCamara()->setVelocidadMovimiento(0.25);
		}
	}*/

	if (key==27)
	{
		glutReshapeWindow(_ventana.getHeight(), _ventana.getWidth());
		exit(0);
	}
}

void ConfiguracionJuego::keyboardCallBack(unsigned char key, int x, int y)
{
	_instancia->keyboard(key, x, y);
}

void ConfiguracionJuego::keyboardUp(unsigned char key, int x, int y)
{
	if(key=='w')
		avanzar = false;
	if(key=='s')
		retroceder = false;
	if(key=='a')
		izquierda = false;
	if(key=='d')
		derecha = false;
	if(key=='c')
	{
		_jugador.setAgachado(false);
		agachado = false;
		_jugador.Agacharse();
	}
}

void ConfiguracionJuego::keyboardUpCallBack(unsigned char key, int x, int y)
{
	_instancia->keyboardUp(key, x, y);
}

void ConfiguracionJuego::movimiento(int x, int y)
{
	_jugador.getCamara()->getAngulo()->mouseMovement(x, y);
}

void ConfiguracionJuego::movimientoCallBack(int x, int y)
{
	_instancia->movimiento(x, y);
}

void ConfiguracionJuego::raton(int boton, int estado, int x, int y)
{
	if(_jugador.getSalud() > 0)
	{
		if((boton == GLUT_LEFT_BUTTON) && (estado == GLUT_DOWN))
			_jugador.getArma()->setDisparado(true);
		if((boton == GLUT_LEFT_BUTTON) && (estado == GLUT_UP))
			_jugador.getArma()->setDisparado(false);
	}
}

void ConfiguracionJuego::ratonCallBack(int boton, int estado, int x, int y)
{
	_instancia->raton(boton, estado, x, y);
}

void ConfiguracionJuego::movimientoJugador()
{
	if(_jugador.getSalud() > 0)
	{
		if(avanzar == true)
			_jugador.getCamara()->avanzar(true);
		if(retroceder == true)
			_jugador.getCamara()->retroceder(true);
		if(derecha == true)
			_jugador.getCamara()->irDerecha();
		if(izquierda == true)
			_jugador.getCamara()->irIzquierda();
		/*if(agachado == true)
			_jugador.Agacharse();*/
	}

//	ALfloat listenerPos[] = {_jugador.getCam().getVector().getX(), _jugador.getCam().getVector().getY(), _jugador.getCam().getVector().getZ()};
//	alListenerfv(AL_POSITION, listenerPos);
}

void ConfiguracionJuego::initMouse()
{
	int centroX = glutGet(GLUT_WINDOW_WIDTH)/2;
	int centroY = glutGet(GLUT_WINDOW_HEIGHT)/2;
	glutWarpPointer(centroX, centroY);
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
}

void ConfiguracionJuego::ReorganizarModelos()
{
	//Aquí se realizará las transformaciones matriciales para la comparacion, las cuales se realizan en este orden: escalado, rotación, traslación (en OpenGL sería glTranslatef, glRotatef, glScalef)
	vector< vector<vector3d> > auxiliar;
	vector< vector<vector3d> > auxiliarOctree;
	//vector< vector<vector3d> > auxiliarBox;
	//vector< vector<vector3d> > auxiliarEsfera;
	vector<Objeto> objetoBoxes, objetoEsferas, objetoOctrees;//, objetoTriangulos;
	vector<vector3d> posicionBoxes, posicionEsferas, posicionOctrees/*, posicionTriangulos*/, rotacionBoxes, rotacionEsferas, rotacionOctrees/*, rotacionTriangulos*/, escaladoBoxes, escaladoEsferas, escaladoOctrees;//, escaladoTriangulos;
	vector<float> gradoBoxes, gradoEsferas, gradoOctrees;//, gradoTriangulos;
	vector<TipoObjeto> tipoBoxes, tipoEsferas, tipoOctrees;

	for(unsigned int i = 0; i < _objeto.size(); i++)
	{
		vector<vector3d> transformadaBox;
		vector<vector3d> transformadaEsfera;
		vector<vector3d> transformada;
		vector<vector3d> transformadaOctree;
		if(_tipoColision[i] == "box")
		{
			objetoBoxes.push_back(_objeto[i]);
			posicionBoxes.push_back(_posicion[i]);
			rotacionBoxes.push_back(_rotacion[i]);
			escaladoBoxes.push_back(_escalado[i]);
			gradoBoxes.push_back(_grados[i]);
			tipoBoxes.push_back(_tipoObjeto[i]);
			vector3d centro, dimensiones;
			transformadaBox = Escalar(_objeto[i].getListaVertices(), _escalado[i]);
			transformadaBox = Rotar(transformadaBox, _escalado[i], _grados[i]);
			transformadaBox = Trasladar(transformadaBox, _posicion[i]);
			ObtenerCentroDimensiones(transformadaBox, centro, dimensiones);
			//auxiliarBox.push_back(transformadaBox);
			Box box(centro, dimensiones.getY(), dimensiones.getZ(), dimensiones.getX());
			_colisionBox.push_back(box);
		}
		if(_tipoColision[i] == "esfera")
		{
			objetoEsferas.push_back(_objeto[i]);
			posicionEsferas.push_back(_posicion[i]);
			rotacionEsferas.push_back(_rotacion[i]);
			escaladoEsferas.push_back(_escalado[i]);
			gradoEsferas.push_back(_grados[i]);
			tipoEsferas.push_back(_tipoObjeto[i]);
			vector3d centro, dimensiones;
			transformadaEsfera = Escalar(_objeto[i].getListaVertices(), _escalado[i]);
			transformadaEsfera = Rotar(transformadaEsfera, _escalado[i], _grados[i]);
			transformadaEsfera = Trasladar(transformadaEsfera, _posicion[i]);
			ObtenerCentroDimensiones(transformadaEsfera, centro, dimensiones);
			//auxiliarEsfera.push_back(transformadaEsfera);
			vector<float> vectorDimensiones = {dimensiones.getX(), dimensiones.getY(), dimensiones.getZ()};
			std::sort(vectorDimensiones.begin(), vectorDimensiones.end(), std::greater<float>());
			Esfera esfera(centro, vectorDimensiones[0]);
			_colisionSphere.push_back(esfera);
		}
		/*if(_tipoColision[i] == "triangulo")
		{
			objetoTriangulos.push_back(_objeto[i]);
			posicionTriangulos.push_back(_posicion[i]);
			rotacionTriangulos.push_back(_rotacion[i]);
			escaladoTriangulos.push_back(_escalado[i]);
			gradoTriangulos.push_back(_grados[i]);
			transformada = Escalar(_objeto[i].getListaVertices(), _escalado[i]);
			transformada = Rotar(transformada, _escalado[i], _grados[i]);
			transformada = Trasladar(transformada, _posicion[i]);
			auxiliar.push_back(transformada);
		}*/
		if(_tipoColision[i] == "octree")
		{
			objetoOctrees.push_back(_objeto[i]);
			posicionOctrees.push_back(_posicion[i]);
			rotacionOctrees.push_back(_rotacion[i]);
			escaladoOctrees.push_back(_escalado[i]);
			gradoOctrees.push_back(_grados[i]);
			tipoOctrees.push_back(_tipoObjeto[i]);
			transformadaOctree = Escalar(_objeto[i].getListaVertices(), _escalado[i]);
			transformadaOctree = Rotar(transformadaOctree, _escalado[i], _grados[i]);
			transformadaOctree = Trasladar(transformadaOctree, _posicion[i]);
			auxiliarOctree.push_back(transformadaOctree);
		}
	}

	//Reordenar el vector de objetos desde el vector de Boxes con insert en este orden: Box, Esfera, Octree, Triangulo
	objetoBoxes.insert(objetoBoxes.end(), objetoEsferas.begin(), objetoEsferas.end());
	objetoBoxes.insert(objetoBoxes.end(), objetoOctrees.begin(), objetoOctrees.end());
	//objetoBoxes.insert(objetoBoxes.end(), objetoTriangulos.begin(), objetoTriangulos.end());
	_objeto = objetoBoxes;
	posicionBoxes.insert(posicionBoxes.end(), posicionEsferas.begin(), posicionEsferas.end());
	posicionBoxes.insert(posicionBoxes.end(), posicionOctrees.begin(), posicionOctrees.end());
	//posicionBoxes.insert(posicionBoxes.end(), posicionTriangulos.begin(), posicionTriangulos.end());
	_posicion = posicionBoxes;
	rotacionBoxes.insert(rotacionBoxes.end(), rotacionEsferas.begin(), rotacionEsferas.end());
	rotacionBoxes.insert(rotacionBoxes.end(), rotacionOctrees.begin(), rotacionOctrees.end());
	//rotacionBoxes.insert(rotacionBoxes.end(), rotacionTriangulos.begin(), rotacionTriangulos.end());
	_rotacion = rotacionBoxes;
	escaladoBoxes.insert(escaladoBoxes.end(), escaladoEsferas.begin(), escaladoEsferas.end());
	escaladoBoxes.insert(escaladoBoxes.end(), escaladoOctrees.begin(), escaladoOctrees.end());
	//escaladoBoxes.insert(escaladoBoxes.end(), escaladoTriangulos.begin(), escaladoTriangulos.end());
	_escalado = escaladoBoxes;
	gradoBoxes.insert(gradoBoxes.end(), gradoEsferas.begin(), gradoEsferas.end());
	gradoBoxes.insert(gradoBoxes.end(), gradoOctrees.begin(), gradoOctrees.end());
	//gradoBoxes.insert(gradoBoxes.end(), gradoTriangulos.begin(), gradoTriangulos.end());
	_grados = gradoBoxes;
	tipoBoxes.insert(tipoBoxes.end(), tipoEsferas.begin(), tipoEsferas.end());
	tipoBoxes.insert(tipoBoxes.end(), tipoOctrees.begin(), tipoOctrees.end());
	_tipoObjeto = tipoBoxes;

	/*_objetoColision.resize(auxiliar.size());
	for(unsigned int i = 0; i < auxiliar.size(); i++)
		_objetoColision[i] = auxiliar[i];*/

	for(unsigned int i = 0; i < auxiliarOctree.size(); i++)
	{
		vector3d centro, dimensiones;
		ObtenerCentroDimensiones(auxiliarOctree[i], centro, dimensiones);
		vector<float> vectorDimensiones = {dimensiones.getX(), dimensiones.getY(), dimensiones.getZ()};
		std::sort(vectorDimensiones.begin(), vectorDimensiones.end(), std::greater<float>());
	//	dimensiones.setX(vectorDimensiones[0] + 0.1); dimensiones.setY(vectorDimensiones[0] + 0.1); 
//dimensiones.setZ(vectorDimensiones[0] + 0.1);
		//cout << "Centro: " << centro;
		//cout << "Dimensiones: " << dimensiones << endl;
		Octree *nuevo = new Octree(centro, dimensiones);
		nuevo->crearOctree(auxiliarOctree[i]);
		_colisionOctree.push_back(nuevo);
	}
}

void ConfiguracionJuego::init()
{
	enable();

	Shader shader; _shader.push_back(shader); _shader.push_back(shader); _shader.push_back(shader); _shader.push_back(shader); _shader.push_back(shader); _shader.push_back(shader); _shader.push_back(shader);
	_shader[0].init("Shaders/directional_light_1.vert", "Shaders/directional_light_1.frag");
	_shader[1].init("Shaders/directional_light_2.vert", "Shaders/directional_light_2.frag");
	_shader[2].init("Shaders/directional_light_3.vert", "Shaders/directional_light_3.frag");
	_shader[3].init("Shaders/texture.vert", "Shaders/texture.frag");
	_shader[4].init("Shaders/textured_light_1.vert", "Shaders/textured_light_1.frag");
	_shader[5].init("Shaders/textured_light_2.vert", "Shaders/textured_light_2.frag");
	_shader[6].init("Shaders/normal_mapping_directional_light.vert", "Shaders/normal_mapping_directional_light.frag");

	/*shader1.init("Shaders/directional_light_3.vert", "Shaders/directional_light_3.frag");
	shader2.init("Shaders/textured_light_2.vert", "Shaders/textured_light_2.frag");
	objeto.CargaOBJ("roca.obj");*/

	if(_areaCesped.size() > 0)
	{
		IniciarHierba();
		//CrearCesped(vector3d(0, -10, 0), vector3d(3, -10, 3), _cesped, _colorCesped);
		for(unsigned int i = 0; i < _areaCesped.size(); i = i + 2)
		{
			CrearCesped(_areaCesped[i], _areaCesped[i + 1], _cesped, _colorCesped);
		}
	}

	_objeto.resize(_modelo.size());
	for(unsigned int i = 0; i < _modelo.size(); i++)
	{
		_objeto[i].CargaOBJ(_modelo[i]);
	}

	for(unsigned int i = 0; i < _indiceObjetos.size(); i++)
	{
		_objeto.push_back(_objeto[_indiceObjetos[i]]);
	}

	//Aquí se realizará las transformaciones matriciales para la comparacion, las cuales se realizan en este orden: escalado, rotación, traslación (en OpenGL sería glTranslatef, glRotatef, glScalef)
	ReorganizarModelos();

	listener(_jugador.getCam().getVector());
	for(unsigned int i = 0; i < _sonidos.size(); i++)
	{
		//_sonidos[i].listener(_jugador.getCam().getVector());
		_sonidos[i].leerFichero();
		_sonidos[i].actualizarSonido(_posicionSonido[i]);
	}

	for(unsigned int i = 0; i < _sonidos.size(); i++)
	{
		_sonidos[i].reproducirSonido();
	}

	_luces.IniciarIluminacion();

	if(_existeCielo)
	{
		_cielo.push_back(LoadBitmap(_parteCielo[0]));
		_cielo.push_back(LoadBitmap(_parteCielo[1]));
		_cielo.push_back(LoadBitmap(_parteCielo[2]));
		_cielo.push_back(LoadBitmap(_parteCielo[3]));
		_cielo.push_back(LoadBitmap(_parteCielo[4]));
		_cielo.push_back(LoadBitmap(_parteCielo[5]));
	}

	_enemigos.push_back(Enemigo());
}

void ConfiguracionJuego::enable()
{
	glEnable (GL_DEPTH_TEST); //enable the depth testing
	glDepthFunc(GL_LESS);
	//glEnable (GL_LIGHTING); //enable the lighting
	//glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
//	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	//glEnable (GL_COLOR_MATERIAL); //if you still want to have lighting on you should enable the GL_COLOR_MATERIAL flag but why it shoun't work without the light is quite strange
//	glEnable (GL_NORMALIZE);
	//glShadeModel (GL_SMOOTH); //set the shader to smooth shader
}

void ConfiguracionJuego::CargaConfiguracion(string fichero)
{
	ifstream flujo(fichero.c_str(), ios::in);
	if(!flujo)
	{
		cerr << "No se puede abrir " << fichero << endl;
		exit(1);
	}

	vector<vector3d> vectorPosicion, vectorRotacion, vectorEscalado;
	vector<string> vectorColision;
	vector<float> vectorAngulo;
	vector<TipoObjeto> vectorTipoObjeto;
	string linea;
	while(getline(flujo, linea))
	{
		if(strcmp(linea.substr(0,7).c_str(), "modelo ") == 0)
		{
			// split string c++: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
			istringstream contenido(linea.substr(7));

			if(NumeroElementos(contenido.str()) >= 12)
			{
				string nombre, tipo_colision;
				float x, y, z, rotX, rotY, rotZ, escalX, escalY, escalZ, grados;
				contenido >> nombre;
				vector3d posicion; contenido >> x; contenido >> y; contenido >> z;
				posicion.setX(x); posicion.setY(y); posicion.setZ(z);

				contenido >> grados;
				vector3d rotacion; contenido >> rotX; contenido >> rotY; contenido >> rotZ;
				rotacion.setX(rotX); rotacion.setY(rotY); rotacion.setZ(rotZ);

				vector3d escalado; contenido >> escalX; contenido >> escalY; contenido >> escalZ;
				escalado.setX(escalX); escalado.setY(escalY); escalado.setZ(escalZ);
				contenido >> tipo_colision;
				_modelo.push_back(nombre);
				_posicion.push_back(posicion);
				_grados.push_back(grados);
				_rotacion.push_back(rotacion);
				_escalado.push_back(escalado);
				_tipoColision.push_back(tipo_colision);
				if(NumeroElementos(contenido.str()) > 12)
				{
					string tipo; contenido >> tipo;
					if(tipo == "objeto")
						_tipoObjeto.push_back(OBJETO);
					else if(tipo == "destructible")
						_tipoObjeto.push_back(DESTRUCTIBLE);
					else if(tipo == "botiquin")
						_tipoObjeto.push_back(BOTIQUIN);
					else if(tipo == "municion")
						_tipoObjeto.push_back(MUNICION);
					else
						_tipoObjeto.push_back(OBJETO);
				}
				if(NumeroElementos(contenido.str()) == 12)
				{
					_tipoObjeto.push_back(OBJETO);
				}
			}
		}
		if(strcmp(linea.substr(0,10).c_str(), "modelomd5 ") == 0)
		{
			// split string c++: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
			istringstream contenido(linea.substr(10));

			if(NumeroElementos(contenido.str()) >= 12)
			{
				string nombre, tipo_colision;
				float x, y, z, rotX, rotY, rotZ, escalX, escalY, escalZ, grados;
				contenido >> nombre;
				vector3d posicion; contenido >> x; contenido >> y; contenido >> z;
				posicion.setX(x); posicion.setY(y); posicion.setZ(z);

				contenido >> grados;
				vector3d rotacion; contenido >> rotX; contenido >> rotY; contenido >> rotZ;
				rotacion.setX(rotX); rotacion.setY(rotY); rotacion.setZ(rotZ);

				vector3d escalado; contenido >> escalX; contenido >> escalY; contenido >> escalZ;
				escalado.setX(escalX); escalado.setY(escalY); escalado.setZ(escalZ);
				contenido >> tipo_colision;
				_modelo.push_back(nombre);
				_posicion.push_back(posicion);
				_grados.push_back(grados);
				_rotacion.push_back(rotacion);
				_escalado.push_back(escalado);
				_tipoColision.push_back(tipo_colision);
				if(NumeroElementos(contenido.str()) > 12)
				{
					string tipo; contenido >> tipo;
					if(tipo == "objeto")
						_tipoObjeto.push_back(OBJETO);
					else if(tipo == "destructible")
						_tipoObjeto.push_back(DESTRUCTIBLE);
					else if(tipo == "botiquin")
						_tipoObjeto.push_back(BOTIQUIN);
					else if(tipo == "municion")
						_tipoObjeto.push_back(MUNICION);
					else
						_tipoObjeto.push_back(OBJETO);
				}
				if(NumeroElementos(contenido.str()) == 12)
				{
					_tipoObjeto.push_back(OBJETO);
				}
			}
		}
		else if(strcmp(linea.substr(0,7).c_str(), "cesped ") == 0)
		{
			istringstream contenido(linea.substr(7));
			if(NumeroElementos(contenido.str()) == 6)
			{
				float origX, origY, origZ, destX, destY, destZ;
				contenido >> origX; contenido >> origY; contenido >> origZ;
				contenido >> destX; contenido >> destY; contenido >> destZ;
				vector3d origen(origX, origY, origZ); vector3d destino(destX, destY, destZ);
				_areaCesped.push_back(origen); _areaCesped.push_back(destino);
			}
		}
		else if(strcmp(linea.substr(0,7).c_str(), "camara ") == 0)
		{
			istringstream contenido(linea.substr(7));
			if(NumeroElementos(contenido.str()) >= 3)
			{
				float PosX, PosY, PosZ, anguloX, anguloY;
				contenido >> PosX; contenido >> PosY; contenido >> PosZ;
				//Camara camara(PosX, PosY, PosZ);
				//_jugador.getCamara() = camara;
				if(NumeroElementos(contenido.str()) == 5)
				{
					contenido >> anguloX; contenido >> anguloY;
					_jugador.getCamara()->setVector(PosX, PosY, PosZ);
					_jugador.getCamara()->setAngulo(anguloX, anguloY);
				}
			}
		}
		else if(strcmp(linea.substr(0,12).c_str(), "existeCielo ") == 0)
		{
			string contenido(linea.substr(12));
			bool valor = false;
			if(contenido == "true")
				valor = true;
			_existeCielo = valor;
		}
		else if(strcmp(linea.substr(0,6).c_str(), "cielo ") == 0)
		{
			istringstream contenido(linea.substr(6));
			vector<string> partes;
			string auxiliar;
			float tamano;
			contenido >> auxiliar; partes.push_back(auxiliar); auxiliar.clear();
			contenido >> auxiliar; partes.push_back(auxiliar); auxiliar.clear();
			contenido >> auxiliar; partes.push_back(auxiliar); auxiliar.clear();
			contenido >> auxiliar; partes.push_back(auxiliar); auxiliar.clear();
			contenido >> auxiliar; partes.push_back(auxiliar); auxiliar.clear();
			contenido >> auxiliar; partes.push_back(auxiliar); auxiliar.clear();
			contenido >> tamano;

			_parteCielo = partes;
			_tamanoSkybox = tamano;
		}
		else if(strcmp(linea.substr(0,14).c_str(), "posicionCielo ") == 0)
		{
			istringstream contenido(linea.substr(14));
			float x, y, z;
			vector3d posicion; contenido >> x; contenido >> y; contenido >> z;
			posicion.setX(x); posicion.setY(y); posicion.setZ(z);
			_posicionCielo = posicion;
		}
		else if(strcmp(linea.substr(0,7).c_str(), "sonido ") == 0)
		{
			istringstream contenido(linea.substr(7));
			string nombre;
			string bandera;
			bool valor = false;
			contenido >> nombre; contenido >> bandera;

			if(bandera == "true")
				valor = true;
			Sonido auxiliar; auxiliar.setFichero(nombre); auxiliar.setLoop(valor);
			_sonidos.push_back(auxiliar);
		}
		else if(strcmp(linea.substr(0,19).c_str(), "localizacionSonido ") == 0)
		{
			istringstream contenido(linea.substr(19));
			float x, y, z;
			vector3d sonido; contenido >> x; contenido >> y; contenido >> z;
			sonido.setX(x); sonido.setY(y); sonido.setZ(z);
			_posicionSonido.push_back(sonido);
		}
		else if(strcmp(linea.substr(0,12).c_str(), "copiaObjeto ") == 0)
		{
			istringstream contenido(linea.substr(12));
			if(NumeroElementos(contenido.str()) >= 12)
			{
				int indice; contenido >> indice;
				float x, y, z, rotX, rotY, rotZ, escalX, escalY, escalZ;
				string tipo_colision;

				vector3d posicion; contenido >> x; contenido >> y; contenido >> z;
				posicion.setX(x); posicion.setY(y); posicion.setZ(z);

				float grados; contenido >> grados;
				vector3d rotacion; contenido >> rotX; contenido >> rotY; contenido >> rotZ;
				rotacion.setX(rotX); rotacion.setY(rotY); rotacion.setZ(rotZ);

				vector3d escalado; contenido >> escalX; contenido >> escalY; contenido >> escalZ;
				escalado.setX(escalX); escalado.setY(escalY); escalado.setZ(escalZ);

				contenido >> tipo_colision;

				_indiceObjetos.push_back(indice);
				vectorColision.push_back(tipo_colision);
				vectorPosicion.push_back(posicion);
				vectorAngulo.push_back(grados);
				vectorRotacion.push_back(rotacion);
				vectorEscalado.push_back(escalado);

				if(NumeroElementos(contenido.str()) > 12) //Modificar para queden como los otros
				{
					string tipo; contenido >> tipo;
					if(tipo == "objeto")
						//_tipoObjeto.push_back(OBJETO);
						vectorTipoObjeto.push_back(OBJETO);
					else if(tipo == "destructible")
						vectorTipoObjeto.push_back(DESTRUCTIBLE);
					else if(tipo == "botiquin")
						//_tipoObjeto.push_back(BOTIQUIN);
						vectorTipoObjeto.push_back(BOTIQUIN);
					else if(tipo == "municion")
						//_tipoObjeto.push_back(MUNICION);
						vectorTipoObjeto.push_back(MUNICION);
					else
						//_tipoObjeto.push_back(OBJETO);
						vectorTipoObjeto.push_back(OBJETO);
				}
				if(NumeroElementos(contenido.str()) == 12)
				{
					vectorTipoObjeto.push_back(OBJETO);
				}
			}
		}
		/*else if(strcmp(linea.substr(0,5).c_str(), "foco ") == 0)
		{
			Iluminacion foco;
			GLfloat ambiente[3]; GLfloat difusa[3]; GLfloat especular[3]; GLfloat posicion[3];
			istringstream contenido(linea.substr(5));
			if(NumeroElementos(contenido.str()) == 12)
			{
				contenido >> ambiente[0]; contenido >> ambiente[1]; contenido >> ambiente[2];
				contenido >> difusa[0]; contenido >> difusa[1]; contenido >> difusa[2];
				contenido >> especular[0]; contenido >> especular[1]; contenido >> especular[2];
				contenido >> posicion[0]; contenido >> posicion[1]; contenido >> posicion[2];

				foco.setAmbiente(vector3d(ambiente[0], ambiente[1], ambiente[2]));
				foco.setDifusa(vector3d(difusa[0], difusa[1], difusa[2]));
				foco.setEspecular(vector3d(especular[0], especular[1], especular[2]));
				foco.setPosicion(vector3d(posicion[0], posicion[1], posicion[2]));

				_luces.InsertarFoco(foco);
			}
		}*/
		else if(strcmp(linea.substr(0,5).c_str(), "foco ") == 0)
		{
			Iluminacion foco;
			GLfloat posicion[3]; GLfloat color[4];
			istringstream contenido(linea.substr(5));
			if(NumeroElementos(contenido.str()) == 6)
			{
				contenido >> posicion[0]; contenido >> posicion[1]; contenido >> posicion[2];
				contenido >> color[0]; contenido >> color[1]; contenido >> color[2]; color[3] = 0;

				foco.setPosicion(vector3d(posicion[0], posicion[1], posicion[2]));
				foco.setColor(color);

				_luces.InsertarFoco(foco);
			//	_luces.push_back(foco);
			}
		}
		else{}
	}
	//Concatenamos las copias realizadas por sus constructores
	_tipoColision.insert(_tipoColision.end(), vectorColision.begin(), vectorColision.end());
	_posicion.insert(_posicion.end(), vectorPosicion.begin(), vectorPosicion.end());
	_grados.insert(_grados.end(), vectorAngulo.begin(), vectorAngulo.end());
	_rotacion.insert(_rotacion.end(), vectorRotacion.begin(), vectorRotacion.end());
	_escalado.insert(_escalado.end(), vectorEscalado.begin(), vectorEscalado.end());
	_tipoObjeto.insert(_tipoObjeto.end(), vectorTipoObjeto.begin(), vectorTipoObjeto.end());

	flujo.close();
}

vector<string> CadenaAString(string cadena, string delimitador)
{
	vector<string> lista;
	string contenido(cadena);
	size_t pos = 0;
	string token;

	while ((pos = contenido.find(delimitador)) != string::npos)
	{
		token = contenido.substr(0, pos);
		lista.push_back(token);
		contenido.erase(0, pos + delimitador.length());
	}
	lista.push_back(contenido);
	return lista;
}

int NumeroElementos(string cadena)
{
	int contador = 1;
	for(unsigned int i = 0; i < cadena.size(); i++)
	{
		if(isspace(cadena[i]))
			contador++;
	}
	return contador;
}

}
