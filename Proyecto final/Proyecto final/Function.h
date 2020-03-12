#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "Event.h"
#include "Dialog_box.h"
#include "Player.h"
#include "Map_Manager.h"
class Game;
class Function
{
public:
	Function();
	~Function();
	void Start();
	void handleInputs(sf::Keyboard::Key key, bool isPressed);
	void Init(sf::RenderWindow* w, vector<Event> e, string n);
	void Update(sf::Time deltaTime);
	void Render(sf::RenderWindow* w);
	void Destroy();
private:
	friend class Function_Manager;
	void TextBox(string text);
	void setSpeed(float speed, Player* player);
	void GoToMap(const string& map_name, sf::Vector2f pos);
	Game* game;
	vector<Event> events;
	Dialog_box* f_dialogBox;
	int f_nEvent = 0;
	bool f_Active = false, f_working = false, EnterPressed = false, key_pressed = false;
	string f_name;
};

