#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Function.h"
#include "Trigger.h"
class Function_Manager
{
public:
	class Trigger_Pair {
	public:
		Trigger_Pair(Trigger t, Function f) { trig = t; func = f; };
		Trigger trig;
		Function func;
	};
	Function_Manager();
	~Function_Manager();
	void Init();
	void Update(sf::Time deltaTime);
	void Render(sf::RenderWindow* window);
	void Destroy();
	void handleInputs(sf::Keyboard::Key key, bool isPressed);
	void CreateFunction(Trigger trig, Function func);
private:
	//vector<Function> fm_functions;
	//map<Trigger, Function> triggers;
	//map<Trigger, Function>::iterator trigsIt;
	vector<Trigger_Pair> triggers;
	//void StartFunction(string g);
};

