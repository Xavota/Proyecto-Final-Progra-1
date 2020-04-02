#include <SFML/Graphics.hpp>
#include "Animator_Manager.h"
#include "Game.h"

int main()
{
	Game* game = Game::getInstance(); // Obtiene la instancia del Game
	game->Init(); // Inicializa el juego
	game->run(); // Empieza el juego
	game->Destroy(); // Libera la memoria del juego
	return 0;
}