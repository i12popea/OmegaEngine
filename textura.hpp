#ifndef _TEXTURA_HPP_
#define _TEXTURA_HPP_

#define GL_GLEXT_PROTOTYPES
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <GL/glut.h>
#include <GL/glu.h>
#include <FreeImage.h>

using namespace std;
using std::string;

extern GLuint textureID;

extern int LoadBitmap(string filename);

#endif
