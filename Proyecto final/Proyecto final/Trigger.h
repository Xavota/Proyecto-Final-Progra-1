#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
using namespace std;
class Trigger
{
public:
	enum triggers {
		on_trigger_enter, on_triger_exit, on_trigger_stay, on_key_pressed, on_key_released, on_key, on_interact
	};
	Trigger();
	~Trigger();
	void Init();
	void Update(sf::Time deltaTime);
	void Render(sf::RenderWindow* window);
	void Destory();
	void handleInputs(sf::Keyboard::Key key, bool isPressed);
	bool TriggerIsMet();
	static Trigger* onTriggerEnter(int x1, int y1, int x2, int y2, Player* player);
	static Trigger* onTriggerExit(int x1, int y1, int x2, int y2, Player* player);
	static Trigger* onTriggerStay(int x1, int y1, int x2, int y2, Player* player);
	static Trigger* onKeyPressed();
	static Trigger* onKeyReleased();
	static Trigger* onKey();
	static Trigger* onInteract(Object* interactuable, Player* player);
private:
	bool inside = false;
	bool EnterPressed = false, key_pressed = false;
	triggers type;
	sf::RectangleShape t_zones;
	Player* g_player;
	Object* t_Interactuable;
};
