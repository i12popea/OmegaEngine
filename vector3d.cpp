#include "vector3d.hpp"
 
using namespace std;
using namespace ed;
 
namespace ed{
 
vector3d vector3d::operator + (vector3d const &vector)
{
    vector3d aux;
    aux.setX(getX() + vector.getX());
    aux.setY(getY() + vector.getY());
    aux.setZ(getZ() + vector.getZ());
    return aux;
}
 
vector3d vector3d::operator - (const vector3d &vector)
{
    vector3d aux;
    aux.setX(getX() - vector.getX());
    aux.setY(getY() - vector.getY());
    aux.setZ(getZ() - vector.getZ());
    return aux;
}
 
vector3d vector3d::operator * (int numero)
{
    vector3d aux;
    aux.setX(getX() * numero);
    aux.setY(getY() * numero);
    aux.setZ(getZ() * numero);
    return aux;
}

vector3d vector3d::operator * (float numero)
{
    vector3d aux;
    aux.setX(getX() * numero);
    aux.setY(getY() * numero);
    aux.setZ(getZ() * numero);
    return aux;
}

vector3d vector3d::operator / (int numero)
{
    vector3d aux;
    if (numero != 0)
    {
        aux.setX(getX() / numero);
        aux.setY(getY() / numero);
        aux.setZ(getZ() / numero);
        return aux;
    }
    else
        return vector3d();
}
 
vector3d& vector3d::operator = (vector3d const &vector)
{
    if(this != &vector)
    {
        setX(vector.getX());
        setY(vector.getY());
        setZ(vector.getZ());
    }
    return *this;
}
 
bool vector3d::operator == (vector3d const &vector)
{
    if (getX() == vector.getX() && getY() == vector.getY() && getZ() == vector.getZ())
        return true;
    else
        return false;
}
 
bool vector3d::operator != (vector3d const &vector)
{
    if (getX() == vector.getX() || getY() == vector.getY() || getZ() == vector.getZ())
        return true;
    else
        return false;
}
 
std::ostream &operator << (std::ostream &stream, const vector3d &vector)
{
    stream << "(" << vector._x << ", " << vector._y << ", " << vector._z << ")" << endl;
    return stream;
}
 
void vector3d::setVector(float x, float y, float z)
{
    setX(x);
    setY(y);
    setZ(z);
}
 
void vector3d::setVector(vector3d vector)
{
    setX(vector.getX());
    setY(vector.getY());
    setZ(vector.getZ());
}
 
//Calculo del modulo conociendo sus componentes
float vector3d::modulo()
{
    return sqrt(pow(getX(), 2) + pow(getY(), 2) + pow(getZ(), 2));
}
float vector3d::modulo(vector3d vector)
{
    return sqrt(pow(vector.getX(), 2) + pow(vector.getY(), 2) + pow(vector.getZ(), 2));
}
float vector3d::productoEscalar(const vector3d &vector)
{
    return (getX()*vector.getX() + getY()*vector.getY() + getZ()*vector.getZ());
}
vector3d vector3d::productoVectorial(const vector3d &vector)
{
    float x, y, z;
    x = getY()*vector.getZ() - vector.getY()*getZ();
    y = getZ()*vector.getX() - vector.getZ()*getX();
    z = getX()*vector.getY() - vector.getX()*getY();
    return vector3d(x, y, z);
}
//Distancia entre 2 puntos
float vector3d::modulo(vector3d vector1, vector3d vector2)
{
    return sqrt(pow(vector2.getX() - vector1.getX(), 2) + pow(vector2.getY() - vector1.getY(), 2) + pow(vector2.getZ() - vector1.getZ(), 2));
}
void vector3d::normalizarVector()
{
    float modulo = (*this).modulo();
    if (modulo != 0)
    {
        setX(getX()/modulo);
        setY(getY()/modulo);
        setZ(getZ()/modulo);
    }
}

vector3d productoVectorial(const vector3d &vector1, const vector3d &vector2)
{
    float x, y, z;
    x = vector1.getY()*vector2.getZ() - vector2.getY()*vector1.getZ();
    y = vector1.getZ()*vector2.getX() - vector2.getZ()*vector1.getX();
    z = vector1.getX()*vector2.getY() - vector2.getX()*vector1.getY();
    return vector3d(x, y, z);
}

float productoEscalar(const vector3d &vector1, const vector3d &vector2)
{
    return (vector1.getX()*vector2.getX() + vector1.getY()*vector2.getY() + vector1.getZ()*vector2.getZ());
}

float modulo(vector3d vector)
{
    return sqrt(pow(vector.getX(), 2) + pow(vector.getY(), 2) + pow(vector.getZ(), 2));
}

vector3d normalizarVector(vector3d vector)
{
    float mod = modulo(vector);
    float x, y, z;
    x = vector.getX()/mod;
    y = vector.getY()/mod;
    z = vector.getZ()/mod;
    return vector3d(x, y, z);
}

vector2d& vector2d::operator = (vector2d const &vector)
{
    if(this != &vector)
    {
        setU(vector.getU());
        setV(vector.getV());
    }
    return *this;
}
 
}
