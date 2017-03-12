#ifndef _FSM_HPP_
#define _FSM_HPP_

#include <iostream>
#include <cmath>

using namespace std;

namespace ed{

enum Estado{
    CAMINAR = 0,
    MUERTO,
    PERSEGUIR,
    CAMBIARDIR,
    ACTIVO,
    ESQUIVAR,
    ATACAR
};

class FSM
{
private:
	Estado _estado;
public:
	FSM(Estado estado = CAMINAR)
	{
		_estado = estado;
	}
	inline void setEstado(Estado estado)
	{
		 _estado = estado;
	}
	inline Estado getEstado()
	{
		return _estado;
	}
};

}

/*
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

enum Estado{
    RUN = 0,
    LEAF,
    HOME
};

class vec3d{
private:
public:
    float _x, _y, _z;
    vec3d(float x = 0, float y = 0, float z = 0)
    {_x = x; _y = y; _z = z;}
};

class FSM{
private:
    Estado _estado;
    void otherFunction();
public:
    inline void setEstado(Estado estado)
    {
        _estado = estado;
    }
    inline Estado getEstado()
    {
        return _estado;
    }
    
    void update()
    {}
};

class Ant{
private:
    vec3d _posicion;
    vec3d _velocidad;
    FSM _brain;
public:
    Ant(float posX = 0, float posY = 0, float posZ = 0){}
    void findLeaf()
    {
        if(5 <= 10)
            _brain.setEstado(HOME);
        if(5 <= 10)
            _brain.setEstado(RUN);
    }
    void goHome()
    {
        if(5 <= 10)
            _brain.setEstado(LEAF);
    }
    void runAway()
    {
        if(5 > 10)
            _brain.setEstado(LEAF);
    }
    void update()
    {
        _brain.update();
    }
};

int main()
{
    Ant hormiga;
}
*/


// Función como argumento
/*#include <iostream>
using namespace std;

void myOtherFunction() {
        cout << "And this is the result.\n";
}

void myFunction(void otherFunction()) {
	otherFunction();
}

int main() {
	myFunction(myOtherFunction);
	return 0;
}*/

//Prueba
/*
// http://www.cplusplus.com/forum/beginner/6596/
#include <iostream>
using namespace std;

void Function1()
{
    cout << "Function 1.\n";
}

void Function2()
{
    cout << "Function 2.\n";
}

class FSM{
private:
    void (*_otherFunction)();
public:
    inline void setEstado(void (*funcion)())
    {
        _otherFunction = funcion;
    }
    void update()
    {
        _otherFunction();
    }
};

int main() {
	FSM maquina;
	maquina.setEstado(Function1);
	maquina.update();
	maquina.update();
	maquina.setEstado(Function2);
	maquina.update();
	return 0;
}
*/

//Segunda prueba
/*
#include <iostream>
#include <cmath>
using namespace std;

float leafX = 0, leafZ = 0, cursorX = 0, cursorZ = 0, homeX = 0, homeZ = 0;

enum Estado{
    LEAF = 0,
    HOME,
    RUN
};

class vec3d{
private:
public:
    float _x, _y, _z;
    vec3d(float x = 0, float y = 0, float z = 0)
    {_x = x; _y = y; _z = z;}
};

vec3d _posicion, _velocidad;

void findLeaf()
{
    cout << "Find Leaf.\n";
}

void goHome()
{
    cout << "Go Home.\n";
}

void runAway()
{
    cout << "Run Away.\n";
}

class FSM{
private:
    void (*_otherFunction)();
public:
    FSM(void (*funcion)() = findLeaf)
    {
        _otherFunction = funcion;
    }
    inline void setEstado(void (*funcion)())
    {
        _otherFunction = funcion;
    }
    void update()
    {
        _otherFunction();
    }
};

FSM MaquinaEstados;

void actualizar()
{
    //Find Leaf
    if(abs(_posicion._x - leafX) <= 10 && abs(_posicion._z - leafZ) <= 10)
    {
        MaquinaEstados.setEstado(goHome);
        MaquinaEstados.update();
    }
    if(abs(_posicion._x - cursorX) <= 50 && abs(_posicion._z - cursorZ) <= 50)
    {
        MaquinaEstados.setEstado(runAway);
        MaquinaEstados.update();
    }
    
    //Go Home
    if(abs(_posicion._x - homeX) <= 10 && abs(_posicion._z - homeZ) <= 10)
    {
        MaquinaEstados.setEstado(findLeaf);
        MaquinaEstados.update();
    }
    
    //Run Away
    if(abs(_posicion._x - cursorX) > 50 && abs(_posicion._z - cursorZ) > 50)
    {
        MaquinaEstados.setEstado(findLeaf);
        MaquinaEstados.update();
    }
}

int main() {
    actualizar();
	//FSM maquina;
	//maquina.setEstado(findLeaf);
	//maquina.update();
	//maquina.update();
	//maquina.setEstado(goHome);
	//maquina.update();
	return 0;
}
*/

//Final
/*
#include <iostream>
#include <cmath>
using namespace std;

float leafX = 0, leafZ = 0, cursorX = 0, cursorZ = 0, homeX = 0, homeZ = 0;

enum Estado{
    LEAF = 0,
    HOME,
    RUN
};

class vec3d{
private:
public:
    float _x, _y, _z;
    vec3d(float x = 0, float y = 0, float z = 0)
    {_x = x; _y = y; _z = z;}
};

class FSM{
private:
    Estado _estado;
public:
    FSM(Estado estado = LEAF){_estado = estado;}
    inline void setEstado(Estado estado)
    {
        _estado = estado;
    }
    inline Estado getEstado()
    {
        return _estado;
    }
};

class Ant{
public:
    FSM _brain;
    vec3d _posicion;
    vec3d _velocidad;
    Ant(Estado estado = LEAF)
    {
        _brain.setEstado(estado);
    }
    void findLeaf()
    {
        cout << "Find Leaf.\n";
        if(abs(_posicion._x - leafX) <= 10 && abs(_posicion._z - leafZ) <= 10)
            _brain.setEstado(HOME);
        if(abs(_posicion._x - cursorX) <= 50 && abs(_posicion._z - cursorZ) <= 50)
            _brain.setEstado(RUN);
    }
    void goHome()
    {
        cout << "Go Home.\n";
        if(abs(_posicion._x - homeX) <= 10 && abs(_posicion._z - homeZ) <= 10)
            _brain.setEstado(LEAF);
    }
    void runAway()
    {
        cout << "Run Away.\n";
        if(abs(_posicion._x - cursorX) > 50 && abs(_posicion._z - cursorZ) > 50)
            _brain.setEstado(LEAF);
    }
    void update()
    {
        if(_brain.getEstado() == LEAF)
            findLeaf();
        if(_brain.getEstado() == RUN)
            runAway();
        if(_brain.getEstado() == HOME)
            goHome();
    }
};

int main() {
	Ant hormiga(HOME);
	//	hormiga._brain.setEstado(LEAF);
	hormiga.update();
	hormiga.update();
	hormiga.update();
	hormiga.update();
	return 0;
}
*/

#endif
