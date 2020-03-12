#include <SFML/Graphics.hpp>
#include "Animator_Manager.h"
#include "Game.h"

int main()
{
	Game* game = Game::getInstance();
	game->Init();
	game->run();

	return 0;
}