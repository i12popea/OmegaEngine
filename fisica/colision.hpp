#ifndef _COLISION_HPP_
#define _COLISION_HPP_

#include "../vector3d.hpp"
#include "colisionCubo.hpp"
#include "colisionEsfera.hpp"
#include "colisionCilindro.hpp"
//#include "plano.hpp"
//#include "objloader.hpp"
#include "colisionTriangulo.hpp"
#include "octree.hpp"
#include <vector>

using namespace std;
using std::vector;

#define GRAVEDAD_TIERRA 9.807;
#define GRAVEDAD_LUNA 1.622;
#define GRAVEDAD_MARTE 3.711;
#define GRAVEDAD_JUPITER 24.79;
#define GRAVEDAD_VENUS 8.87;
#define GRAVEDAD_SATURNO 10.44;
#define GRAVEDAD_MERCURIO 3.7;
#define GRAVEDAD_NEPTUNO 11.15;
#define GRAVEDAD_URANO 8.69;
#define GRAVEDAD_PLUTON 0.658;
#define GRAVEDAD_TITAN 1.352;

namespace ed{

float distanciaX(Esfera uno, Esfera dos);
float distanciaY(Esfera uno, Esfera dos);
float distanciaZ(Esfera uno, Esfera dos);
float distanciaX(vector3d uno, vector3d dos);
float distanciaY(vector3d uno, vector3d dos);
float distanciaZ(vector3d uno, vector3d dos);
float distancia(Esfera uno, Esfera dos);
float distanciaEntrePuntos(vector3d uno, vector3d dos);
float distanciaEntrePuntos2D(vector3d uno, vector3d dos);
bool interseccion(Box uno, Box dos);
bool interseccion(Esfera esferaUno, Esfera esferaDos);
bool interseccion(Esfera esfera, vector3d punto);
bool interseccion(Box cubo, vector3d punto);
bool interseccion(Esfera esfera, Box cubo);

bool ColisionCilindroEsfera(Esfera esfera, Cilindro cilindro, bool &colSuelo, bool &colTecho, bool &colPared, float &difX, float &difZ);
void ReaccionCilindroEsfera(vector3d &posicion, bool colSuelo, bool colTecho, bool colPared, Esfera esfera, Cilindro cilindro, float difX, float difZ);
bool ColisionCilindroOcteto(Box octeto, Cilindro cilindro, bool &colSuelo, bool &colTecho, bool &colPared, float &difX, float &difZ);
void ReaccionCilindroOcteto(vector3d &posicion, bool colSuelo, bool colTecho, bool colPared, Box octeto, Cilindro cilindro, float difX, float difZ);

/*
#include <iostream>
#include <cmath>

using namespace std;

class Rectangulo
{
public:
    float x, y, z;
    float alto, largo, ancho;
};

class Circulo
{
public:
    float r;
    float x, y, z;
    float altura;
    float unoX, unoY, unoZ;
    float dosX, dosY, dosZ;
};

bool colision (Circulo circle, Rectangulo rect)
{
   //float distanciaArriba = abs(circle.unoY - rect.y - rect.alto/2);
   //float distanciaAbajo = abs(circle.dosY - rect.y - rect.alto/2);
   float distanciaAltura = abs((circle.dosY - circle.unoY)/2 - rect.y);
   cout << "altura: " << distanciaAltura << endl;
   cout << "tam altura: " << ((circle.dosY - circle.unoY)/2 + rect.alto) << endl;
   
   float circleDistanceX = abs(abs(circle.unoX - rect.x) - rect.ancho/2);
   float circleDistanceZ = abs(abs(circle.unoZ - rect.z) - rect.largo/2);
   cout << "circleDistanceX: " << circleDistanceX << endl;
   cout << "circleDistanceZ: " << circleDistanceZ << endl;
 
   //if( (circleDistanceX > (rect.ancho/2 + circle.r)) || (distanciaArriba > (rect.y + rect.alto/2)) || (distanciaAbajo > (rect.y + rect.alto/2)) )
   if( (circleDistanceX > (rect.ancho/2 + circle.r)) )
   { cout << "No 1\n"; return false; }
   //if( (circleDistanceZ > (rect.largo/2 + circle.r)) || (distanciaArriba > (rect.y + rect.alto/2)) || (distanciaAbajo > (rect.y + rect.alto/2)) )
   if( (circleDistanceZ > (rect.largo/2 + circle.r)) )
   { cout << "No 2\n"; return false; }
 
   //if( (circleDistanceX <= (rect.ancho/2)) || (distanciaArriba <= (rect.y + rect.alto/2)) || (distanciaAbajo <= (rect.y + rect.alto/2)) )
   if( (circleDistanceX <= (rect.ancho/2)) && (distanciaAltura <= ((circle.dosY - circle.unoY)/2 + rect.alto)) )
   { cout << "Si 1\n"; return true; }
   //if( (circleDistanceZ <= (rect.largo/2)) || (distanciaArriba <= (rect.y + rect.alto/2)) || (distanciaAbajo <= (rect.y + rect.alto/2)) )
   if( (circleDistanceZ <= (rect.largo/2)) && (distanciaAltura <= ((circle.dosY - circle.unoY)/2 + rect.alto)) )
   { cout << "Si 2\n"; return true; }
 
   float cornerDistance_sq = pow(circleDistanceX - rect.ancho/2, 2) + pow(circleDistanceZ - rect.largo/2, 2);
 
   //return (cornerDistance_sq <= (pow(circle.r, 2)));
   if(cornerDistance_sq <= (pow(circle.r, 2)) && (distanciaAltura <= ((circle.dosY - circle.unoY)/2 + rect.alto)))
   {
       cout << "Si 3\n";
       return true;
   }
   else
   {
       cout << "No 3\n";
       return false;
   }
}

int main()
{
    Rectangulo rect; rect.x = 1; rect.y = 3; rect.z = 0; rect.largo = 1; rect.ancho = 1; rect.largo = 1;
    Circulo circle; circle.r = 0.9;
    circle.altura = 2; circle.x = 3; circle.y = 0; circle.z = 0;
    circle.unoX = 3; circle.unoY = 0; circle.unoZ = 0; circle.dosX = 3; circle.dosY = 3; circle.dosZ = 0;
    
    if(colision(circle, rect))
        cout << "Hay colision\n";
    else
        cout << "No hay colision\n";
}
*/

/*
#include <iostream>
#include <cmath>

using namespace std;

class Rectangulo
{
public:
    float x, y, z;
    float alto, largo, ancho;
};

class Circulo
{
public:
    float r;
    float x, y, z;
    float altura;
};

bool colision (Circulo circle, Rectangulo rect)
{
   //float distanciaArriba = abs(circle.unoY - rect.y - rect.alto/2);
   //float distanciaAbajo = abs(circle.dosY - rect.y - rect.alto/2);
   float distanciaAltura = abs(circle.y - rect.y);
   cout << "altura: " << distanciaAltura << endl;
   cout << "tam altura: " << (circle.y + rect.alto) << endl;
   
   float circleDistanceX = abs(abs(circle.x - rect.x) - rect.ancho/2);
   float circleDistanceZ = abs(abs(circle.z - rect.z) - rect.largo/2);
   cout << "circleDistanceX: " << circleDistanceX << endl;
   cout << "circleDistanceZ: " << circleDistanceZ << endl;
 
   //if( (circleDistanceX > (rect.ancho/2 + circle.r)) || (distanciaArriba > (rect.y + rect.alto/2)) || (distanciaAbajo > (rect.y + rect.alto/2)) )
   if( (circleDistanceX > (rect.ancho/2 + circle.r)) )
   { cout << "No 1\n"; return false; }
   //if( (circleDistanceZ > (rect.largo/2 + circle.r)) || (distanciaArriba > (rect.y + rect.alto/2)) || (distanciaAbajo > (rect.y + rect.alto/2)) )
   if( (circleDistanceZ > (rect.largo/2 + circle.r)) )
   { cout << "No 2\n"; return false; }
 
   //if( (circleDistanceX <= (rect.ancho/2)) || (distanciaArriba <= (rect.y + rect.alto/2)) || (distanciaAbajo <= (rect.y + rect.alto/2)) )
   if( (circleDistanceX <= (rect.ancho/2)) && (distanciaAltura <= (circle.altura + rect.alto)) )
   {
       cout << "Si 1\n";
       if( (rect.y - rect.alto <= circle.y + circle.altura) && (rect.y - rect.alto > circle.y) )
          cout << "Techo\n";
       else if( (rect.y + rect.alto >= circle.y - circle.altura) && (rect.y + rect.alto < circle.y) )
          cout << "Suelo\n";
       else
          cout << "Pared\n";
       return true;
   }
   //if( (circleDistanceZ <= (rect.largo/2)) || (distanciaArriba <= (rect.y + rect.alto/2)) || (distanciaAbajo <= (rect.y + rect.alto/2)) )
   if( (circleDistanceZ <= (rect.largo/2)) && (distanciaAltura <= (circle.altura + rect.alto)) )
   {
       cout << "Si 2\n";
       if( (rect.y - rect.alto <= circle.y + circle.altura) && (rect.y - rect.alto > circle.y) )
          cout << "Techo\n";
       else if( (rect.y + rect.alto >= circle.y - circle.altura) && (rect.y + rect.alto < circle.y) )
          cout << "Suelo\n";
       else
          cout << "Pared\n";
       return true;
   }
 
   float cornerDistance_sq = pow(circleDistanceX - rect.ancho/2, 2) + pow(circleDistanceZ - rect.largo/2, 2);
 
   //return (cornerDistance_sq <= (pow(circle.r, 2)));
   if(cornerDistance_sq <= (pow(circle.r, 2)) && (distanciaAltura <= (circle.altura + rect.alto)))
   {
       cout << "Si 3\n";
       return true;
   }
   else
   {
       cout << "No 3\n";
       return false;
   }
}

int main()
{
    Rectangulo rect; rect.x = 2; rect.y = 5; rect.z = 0; rect.alto = 1; rect.ancho = 1; rect.largo = 1;
    Circulo circle; circle.r = 1;
    circle.altura = 2; circle.x = 0; circle.y = 2; circle.z = 0;
    
    if(colision(circle, rect))
        cout << "Hay colision\n";
    else
        cout << "No hay colision\n";
}
*/

}


#endif
