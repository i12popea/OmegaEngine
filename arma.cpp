#include "arma.hpp"

using namespace std;
using namespace ed;

namespace ed{

void Arma::DibujarArma()
{
	GLUquadricObj *bazouka= gluNewQuadric(); 
	glPushMatrix();
	glEnable (GL_TEXTURE_2D);

	glLoadIdentity();
	glTranslatef(0,0,-1.9);
	glTranslatef(0, -0.8, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	gluQuadricTexture(bazouka, 1);
	gluQuadricDrawStyle(bazouka, GLU_FILL);
	gluCylinder(bazouka,0.2,0.2,1.5,75,3);
	gluDeleteQuadric(bazouka);

	glDisable (GL_TEXTURE_2D);
	glPopMatrix();
}

void Arma::DibujarProyectil(vector3d posicion, vector3d objetivo, float xrot, float yrot)
{
	if(_EsDisparado == false)
	{
		/*vector3d objetivo;
		objetivo.setX(50*cos(angulo.x)*sin(angulo.y));
		objetivo.setY(50*sin(angulo.x));
		objetivo.setZ(50*cos(angulo.x)*cos(angulo.y));*/
		_posicion.setVector(posicion.getX(), posicion.getY() - 0.8f, posicion.getZ());		//Este es para los modos normales
		//_posicion = vector3d(posicion.getX(), posicion.getY() - 0.8f, posicion.getZ());
		//_posicion = posicion;		//Este se usa para centrar el proyectil con la mira como en algunos modos de disparo
		_salida = _posicion;
		_objetivo = objetivo;
		_xrot = xrot;
		_yrot = yrot;
	}
	for(unsigned int i = 0; i < _municionDisparada.size(); i++)
	{
		vector3d auxiliar;

		//Este se usa para el modo normal de disparo
		auxiliar.setX(_municionDisparada[i].getPosicion().getX() + _municionDisparada[i].getObjetivo().getX());
		auxiliar.setY(_municionDisparada[i].getPosicion().getY() + 0.02f*(_municionDisparada[i].getObjetivo().getY() - _municionDisparada[i].getSalida().getY()));
		auxiliar.setZ(_municionDisparada[i].getPosicion().getZ() - _municionDisparada[i].getObjetivo().getZ());

		_municionDisparada[i].setPosicion(auxiliar);

	//cout << _municionDisparada[i].getPosicion().getX() << ", " << _municionDisparada[i].getPosicion().getY() << ", " << _municionDisparada[i].getPosicion().getZ() << endl;

		glPushMatrix();
		glTranslatef(_municionDisparada[i].getPosicion().getX(), _municionDisparada[i].getPosicion().getY(), _municionDisparada[i].getPosicion().getZ());
		glutSolidSphere(0.2, 20, 20);
		glPopMatrix();
	}
}

void Arma::Disparo()
{
	if(_municion > 0)
	{
		_municion--;

		Municion proyectil;
		/*proyectil.setObjetivo(_posicion);
		proyectil.setSalida(_objetivo);
		proyectil.setPosicion(proyectil.getPosicion() + ((proyectil.getObjetivo() - proyectil.getSalida())*0.02f));*/
		proyectil.setPosicion(_posicion);
		proyectil.setObjetivo(_objetivo);
		proyectil.setSalida(_salida);
		//proyectil.setXrot(_xrot);
		//proyectil.setYrot(_yrot);
		_municionDisparada.push_back(proyectil);

		_sonido.setFichero("sonidos/launch_missile.wav");
		alGetError();
		_sonido.leerFichero();
		//_sonido.actualizarSonido(posicion);
		_sonido.reproducirSonido();
	}
}

void Arma::AumentarMunicion()
{
	//Iniciamos una semilla aleatoria
	srand(time(NULL));
	//Escogemos una cantidad entre 5 y 10
	int cantidad = 5 + ( rand() % ( 10 - 5 + 1 ) );
	_municion = _municion + cantidad;
}

}
