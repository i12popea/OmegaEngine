#ifndef _SKYBOX_HPP_
#define _SKYBOX_HPP_

#include <GL/glu.h>
#include <iostream>
#include "camara.hpp"
#include <vector>

using namespace std;
using namespace ed;
using std::vector;

//void Skybox(Camara camara, vector<int> _skybox);
void Skybox(vector<int> _skybox, float size);

#endif
