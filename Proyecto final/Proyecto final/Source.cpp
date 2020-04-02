#include <SFML/Graphics.hpp>
#include "Animator_Manager.h"
#include "Game.h"

// Sólo trata de interactuar con lo que veas. Difruta :D
// Todo el juego se modifica desde los archivos (casi todo) lo seguré avanzando fuera de clases

int main()
{
	Game* game = Game::getInstance(); // Obtiene la instancia del Game
	game->Init(); // Inicializa el juego
	game->run(); // Empieza el juego
	game->Destroy(); // Libera la memoria del juego
	return 0;
}