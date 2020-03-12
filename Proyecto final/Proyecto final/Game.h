#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Function.h"
#include "Function_Manager.h"
#include "NPC.h"
#include "Map.h"
class Game
{
public:
	static Game* getInstance();
	void run();
	void Init();
	void Destroy();
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
	Player* g_player = new Player({ 64.f, 64.f });
	sf::RenderWindow mWindow;
	bool mIsMovingUp = false, mIsMovingDown = false, mIsMovingLeft = false, mIsMovingRight = false;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	Function func;
	Function_Manager FM;
	NPC* g_npc = new NPC({ 64.f, 64.f });
	vector<Object*> g_objs;
	Map map;
};

