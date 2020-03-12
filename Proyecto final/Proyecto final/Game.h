#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Function.h"
#include "Function_Manager.h"
#include "NPC.h"
#include "Map_Manager.h"
class Game
{
public:
	static Game* getInstance();
	void run();
	void Init();
	void Destroy();
	float pixels = 64.f;
private:
	static Game* instance;
	Game();
	void processEvents();
	void update(sf::Time deltaTime);
	void render(); 
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
	friend class Function;
	friend class Object;
	friend class Player;
	friend class Map;
	friend class Map_Manager;
	Player* g_player = new Player({ pixels, pixels });
	Function_Manager FM;
	NPC* g_npc = new NPC({ pixels, pixels });
	Map_Manager mm;
	sf::RenderWindow mWindow;
	bool mIsMovingUp = false, mIsMovingDown = false, mIsMovingLeft = false, mIsMovingRight = false;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
};