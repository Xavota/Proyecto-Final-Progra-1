#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Function.h"
#include "Trigger.h"
class Function_Manager
{
public:
	Function_Manager();
	~Function_Manager();
	void Init();
	void Update(sf::Time deltaTime);
	void Render(sf::RenderWindow* window);
	void Destroy();
	void handleInputs(sf::Keyboard::Key key, bool isPressed);
	void CreateFunction(sf::RenderWindow* w, vector<Event> e, string n);
	void CreateTrigger(Trigger* trig, const string& func_name);
private:
	vector<Function> fm_functions;
	map<Trigger*, Function*> triggers;
	map<Trigger*, Function*>::iterator trigsIt;
	void StartFunction(string g);
};

