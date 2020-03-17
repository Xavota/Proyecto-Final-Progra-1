#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Map.h";
class Game;
using namespace std;
class Trigger
{
public:
	enum triggers {
		on_trigger_enter, on_triger_exit, on_trigger_stay, on_key_pressed, on_key_released, on_key, on_interact, on_pos_interact, on_map_enter
	};
	Trigger();
	~Trigger();
	void Init();
	void Update(sf::Time deltaTime);
	void Render(sf::RenderWindow* window);
	void Destory();
	void handleInputs(sf::Keyboard::Key key, bool isPressed);
	bool TriggerIsMet();
	static Trigger onTriggerEnter(sf::Vector2i init, sf::Vector2i fin);
	static Trigger onTriggerExit(sf::Vector2i init, sf::Vector2i fin);
	static Trigger onTriggerStay(sf::Vector2i init, sf::Vector2i fin);
	static Trigger onKeyPressed();
	static Trigger onKeyReleased();
	static Trigger onKey();
	static Trigger onInteract(Object* interactuable);
	static Trigger onInteract(sf::Vector2i pos);
	static Trigger onMapEnter(Map* map);
private:
	bool inside = false;
	bool EnterPressed = false, key_pressed = false;
	bool onMap = false;
	triggers type;
	sf::RectangleShape t_zones;
	sf::Vector2f t_pos_interractuable;
private:
	Player* g_player;
	Object* t_Interactuable;
	Map* t_map;
	static Game* game;
};

