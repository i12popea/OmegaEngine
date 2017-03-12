#include "initLoaderJuego.hpp"

using namespace std;
using namespace ed;

int main(int argc, char **argv)
{
	
	ConfiguracionJuego *aplicacion = ConfiguracionJuego::Instancia();
	aplicacion->CargaConfiguracion("prueba.load");
	aplicacion->IniciarFramework(argc, argv);

	return 0;
}
