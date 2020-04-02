#include <SFML/Graphics.hpp>
#include "Animator_Manager.h"
#include "Game.h"

// S�lo trata de interactuar con lo que veas. Difruta :D
// Todo el juego se modifica desde los archivos (casi todo) lo segur� avanzando fuera de clases
// Una acalaraci�n: de el men� de pausa s�lo funcionan el bot�n de reanudar, guardar, cargar y salir
//				    y s�lo se puede guardar y cargar de un archivo (por ahora)

int main()
{
	Game* game = Game::getInstance(); // Obtiene la instancia del Game
	game->Init(); // Inicializa el juego
	game->run(); // Empieza el juego
	game->Destroy(); // Libera la memoria del juego
	return 0;
}