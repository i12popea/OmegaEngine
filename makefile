Juego:
	g++ -Wall -O2 vector3d.cpp textura.cpp menu.cpp mainMenu.cpp -lglut -lGLU -lGL -lfreeimage -o pruebaMenu
#	g++ -Wall -O2 vector3d.cpp textura.cpp mainMenu2.cpp -lglut -lGLU -lGL -lfreeimage -o mainMenu
#	g++ -Wall -std=c++11 -O2 vector3d.cpp quaternion.cpp angulo.cpp camara.cpp sonido.cpp arma.cpp jugador.cpp indicePlano.cpp Frustum.cpp fisica/colisionTriangulo.cpp fisica/octree.cpp fisica/colisionCubo.cpp fisica/colisionCilindro.cpp fisica/colisionEsfera.cpp fisica/colision.cpp fisica/fisicas.cpp objloader.cpp md5modelo.cpp md5animacion.cpp enemigo.cpp textura.cpp skybox.cpp iluminacion.cpp procedural.cpp init.cpp initLoaderJuego.cpp shader.cpp shooter.cpp -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -o test_shooter

	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 shader.cpp -o shader.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 vector3d.cpp -o vector3d.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 quaternion.cpp -o quaternion.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 angulo.cpp -o angulo.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 camara.cpp -o camara.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 sonido.cpp -o sonido.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 arma.cpp -o arma.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 jugador.cpp -o jugador.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 indicePlano.cpp -o indicePlano.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 Frustum.cpp -o Frustum.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 fisica/colisionTriangulo.cpp -o fisica/colisionTriangulo.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 fisica/octree.cpp -o fisica/octree.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 fisica/colisionCubo.cpp -o fisica/colisionCubo.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 fisica/colisionCilindro.cpp -o fisica/colisionCilindro.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 fisica/colisionEsfera.cpp -o fisica/colisionEsfera.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 fisica/colision.cpp -o fisica/colision.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 fisica/fisicas.cpp -o fisica/fisicas.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 objloader.cpp -o objloader.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 md5modelo.cpp -o md5modelo.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 md5animacion.cpp -o md5animacion.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 enemigo.cpp -o enemigo.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 textura.cpp -o textura.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 skybox.cpp -o skybox.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 iluminacion.cpp -o iluminacion.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 procedural.cpp -o procedural.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 init.cpp -o init.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 initLoaderJuego.cpp -o initLoaderJuego.o
	g++ -Wall -std=c++11 -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -c -O2 shooter.cpp -o shooter.o

	g++ -Wall -std=c++11 -O2 vector3d.o quaternion.o angulo.o camara.o sonido.o arma.o jugador.o indicePlano.o Frustum.o fisica/colisionTriangulo.o fisica/octree.o fisica/colisionCubo.o fisica/colisionCilindro.o fisica/colisionEsfera.o fisica/colision.o fisica/fisicas.o objloader.o md5modelo.o md5animacion.o enemigo.o textura.o skybox.o iluminacion.o procedural.o init.o initLoaderJuego.o shader.o shooter.o -lGLEW -lglut -lGLU -lGL -lopenal -lalut -lfreeimage -o test_shooter

	rm *.o
	rm fisica/*.o
