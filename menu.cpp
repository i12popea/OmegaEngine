#include "menu.hpp"

using namespace std;
using namespace ed;


void Menu::IniciarMenu()
{
	int background;
	vector<vector2d> coordBackground; vector<vector3d> posBackground;
	vector3d colorBackground(1.0, 1.0, 1.0);
	background = LoadBitmap("Textures/brick.jpg");
	coordBackground.push_back(vector2d(0.0, 1.0)); coordBackground.push_back(vector2d(1.0, 1.0)); coordBackground.push_back(vector2d(1.0, 0.0)); coordBackground.push_back(vector2d(0.0, 0.0));
	//posBackground.push_back(vector3d(glutGet(GLUT_WINDOW_X), glutGet(GLUT_WINDOW_Y), -1)); posBackground.push_back(vector3d(glutGet(GLUT_WINDOW_X), glutGet(GLUT_WINDOW_Y), -1)); posBackground.push_back(vector3d(glutGet(GLUT_WINDOW_X), glutGet(GLUT_WINDOW_Y), -1)); posBackground.push_back(vector3d(glutGet(GLUT_WINDOW_X), glutGet(GLUT_WINDOW_Y), -1));
	posBackground.push_back(vector3d(0, 0, -1)); posBackground.push_back(vector3d(800, 0, -1)); posBackground.push_back(vector3d(800, 600, -1)); posBackground.push_back(vector3d(0, 600, -1));

	vector<vector2d> coordBoton1; vector<vector3d> posBoton1;
	vector<vector2d> coordBoton2; vector<vector3d> posBoton2;
	vector<vector2d> coordBoton3; vector<vector3d> posBoton3;
	vector<int> botones;
	botones.push_back(LoadBitmap("Textures/boton1.jpg"));
	botones.push_back(LoadBitmap("Textures/boton1.jpg"));
	botones.push_back(LoadBitmap("Textures/boton3.jpg"));
	//vector3d posBoton1(1.0, 0.0, 0.0);

	coordBoton1.push_back(vector2d(0.0, 1.0)); coordBoton1.push_back(vector2d(1.0, 1.0)); coordBoton1.push_back(vector2d(1.0, 0.0)); coordBoton1.push_back(vector2d(0.0, 0.0));
	coordBoton2.push_back(vector2d(0.0, 1.0)); coordBoton2.push_back(vector2d(1.0, 1.0)); coordBoton2.push_back(vector2d(1.0, 0.0)); coordBoton2.push_back(vector2d(0.0, 0.0));
	coordBoton3.push_back(vector2d(0.0, 1.0)); coordBoton3.push_back(vector2d(1.0, 1.0)); coordBoton3.push_back(vector2d(1.0, 0.0)); coordBoton3.push_back(vector2d(0.0, 0.0));

	//posBoton1.push_back(vector3d(200, 200, -1)); posBoton1.push_back(vector3d(400, 200, -1)); posBoton1.push_back(vector3d(400, 400, -1)); posBoton1.push_back(vector3d(200, 400, -1));
	//posBoton1.push_back(vector3d(200, 280, -1)); posBoton1.push_back(vector3d(300, 280, -1)); posBoton1.push_back(vector3d(300, 250, -1)); posBoton1.push_back(vector3d(200, 250, -1));
	posBoton1.push_back(vector3d(200, 200, -1)); posBoton1.push_back(vector3d(300, 200, -1)); posBoton1.push_back(vector3d(300, 300, -1)); posBoton1.push_back(vector3d(200, 300, -1));
	posBoton2.push_back(vector3d(200, 235, -1)); posBoton2.push_back(vector3d(300, 235, -1)); posBoton2.push_back(vector3d(300, 205, -1)); posBoton2.push_back(vector3d(200, 205, -1));
	posBoton3.push_back(vector3d(200, 190, -1)); posBoton3.push_back(vector3d(300, 190, -1)); posBoton3.push_back(vector3d(300, 160, -1)); posBoton3.push_back(vector3d(200, 160, -1));

	vector3d colorBoton1(0.0, 0.0, 0.0);
	vector3d colorBoton2(0.0, 0.0, 0.0);
	vector3d colorBoton3(0.0, 0.0, 0.0);

	_background = background;
	_coordBackground = coordBackground; _posBackground = posBackground;
	_colorBackground = colorBackground;
	_botones = botones;
	_coordBoton1 = coordBoton1; _posBoton1 = posBoton1; _colorBoton1 = colorBoton1;
	_coordBoton2 = coordBoton2; _posBoton2 = posBoton2; _colorBoton2 = colorBoton2;
	_coordBoton3 = coordBoton3; _posBoton3 = posBoton3; _colorBoton3 = colorBoton3;
}

void Menu::MostrarMenu()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _botones[0]);
	glColor3f(_colorBoton1.getX(), _colorBoton1.getY(), _colorBoton1.getZ());
	glBegin(GL_QUADS);
		glTexCoord2f(_coordBoton1[0].getU(), _coordBoton1[0].getV()); glVertex3f(_posBoton1[0].getX(), _posBoton1[0].getY(), _posBoton1[0].getZ());
		glTexCoord2f(_coordBoton1[1].getU(), _coordBoton1[1].getV()); glVertex3f(_posBoton1[1].getX(), _posBoton1[1].getY(), _posBoton1[1].getZ());
		glTexCoord2f(_coordBoton1[2].getU(), _coordBoton1[2].getV()); glVertex3f(_posBoton1[2].getX(), _posBoton1[2].getY(), _posBoton1[2].getZ());
		glTexCoord2f(_coordBoton1[3].getU(), _coordBoton1[3].getV()); glVertex3f(_posBoton1[3].getX(), _posBoton1[3].getY(), _posBoton1[3].getZ());
	glEnd();
	glPopMatrix();

	/*glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _botones[1]);
	glColor3f(_colorBoton2.getX(), _colorBoton2.getY(), _colorBoton2.getZ());
	glBegin(GL_QUADS);
		glTexCoord2f(_coordBoton2[0].getU(), _coordBoton2[0].getV()); glVertex3f(_posBoton2[0].getX(), _posBoton2[0].getY(), _posBoton2[0].getZ());
		glTexCoord2f(_coordBoton2[1].getU(), _coordBoton2[1].getV()); glVertex3f(_posBoton2[1].getX(), _posBoton2[1].getY(), _posBoton2[1].getZ());
		glTexCoord2f(_coordBoton2[2].getU(), _coordBoton2[2].getV()); glVertex3f(_posBoton2[2].getX(), _posBoton2[2].getY(), _posBoton2[2].getZ());
		glTexCoord2f(_coordBoton2[3].getU(), _coordBoton2[3].getV()); glVertex3f(_posBoton2[3].getX(), _posBoton2[3].getY(), _posBoton2[3].getZ());
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _botones[2]);
	glColor3f(_colorBoton3.getX(), _colorBoton3.getY(), _colorBoton3.getZ());
	glBegin(GL_QUADS);
		glTexCoord2f(_coordBoton3[0].getU(), _coordBoton3[0].getV()); glVertex3f(_posBoton3[0].getX(), _posBoton3[0].getY(), _posBoton3[0].getZ());
		glTexCoord2f(_coordBoton3[1].getU(), _coordBoton3[1].getV()); glVertex3f(_posBoton3[1].getX(), _posBoton3[1].getY(), _posBoton3[1].getZ());
		glTexCoord2f(_coordBoton3[2].getU(), _coordBoton3[2].getV()); glVertex3f(_posBoton3[2].getX(), _posBoton3[2].getY(), _posBoton3[2].getZ());
		glTexCoord2f(_coordBoton3[3].getU(), _coordBoton3[3].getV()); glVertex3f(_posBoton3[3].getX(), _posBoton3[3].getY(), _posBoton3[3].getZ());
	glEnd();
	glPopMatrix();*/

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _background);
	glColor3f(_colorBackground.getX(), _colorBackground.getY(), _colorBackground.getZ());
	glBegin(GL_QUADS);
		glTexCoord2f(_coordBackground[0].getU(), _coordBackground[0].getV()); glVertex3f(_posBackground[0].getX(), _posBackground[0].getY(), _posBackground[0].getZ());
		glTexCoord2f(_coordBackground[1].getU(), _coordBackground[1].getV()); glVertex3f(_posBackground[1].getX(), _posBackground[1].getY(), _posBackground[1].getZ());
		glTexCoord2f(_coordBackground[2].getU(), _coordBackground[2].getV()); glVertex3f(_posBackground[2].getX(), _posBackground[2].getY(), _posBackground[2].getZ());
		glTexCoord2f(_coordBackground[3].getU(), _coordBackground[3].getV()); glVertex3f(_posBackground[3].getX(), _posBackground[3].getY(), _posBackground[3].getZ());
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

bool AABBPoint(vector3d esquina1, vector3d esquina2, vector2d punto)
{
	if(esquina1.getX() <= punto.getU() && punto.getU() <= esquina2.getX() && esquina1.getY() <= punto.getV() && punto.getV() <= esquina2.getY())
		return true;
	return false;
}
