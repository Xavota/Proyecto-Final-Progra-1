#include "Function_Manager.h"



Function_Manager::Function_Manager()
{
}


Function_Manager::~Function_Manager()
{
}

void Function_Manager::Init()
{
}

void Function_Manager::Update(sf::Time deltaTime)
{
	for (int i = 0; i < fm_functions.size(); i++) {
		fm_functions[i].Update(deltaTime);
	}
	for (trigsIt = triggers.begin(); trigsIt != triggers.end(); trigsIt++) {
		trigsIt->first->Update(deltaTime);
		if (trigsIt->first->TriggerIsMet()) {
			trigsIt->second->Start();
		}
	}
}

void Function_Manager::handleInputs(sf::Keyboard::Key key, bool isPressed)
{
	for (int i = 0; i < fm_functions.size(); i++) {
		fm_functions[i].handleInputs(key, isPressed);
	}
	for (trigsIt = triggers.begin(); trigsIt != triggers.end(); trigsIt++) {
		trigsIt->first->handleInputs(key, isPressed);
	}
}

void Function_Manager::Render(sf::RenderWindow * window)
{
	for (trigsIt = triggers.begin(); trigsIt != triggers.end(); trigsIt++) {
		trigsIt->first->Render(window);
	}
	for (int i = 0; i < fm_functions.size(); i++) {
		fm_functions[i].Render(window);
	}
}

void Function_Manager::Destroy()
{
	for (trigsIt = triggers.begin(); trigsIt != triggers.end(); trigsIt++) {
		trigsIt->first->Destory();
	}
	for (int i = 0; i < fm_functions.size(); i++) {
		fm_functions[i].Destroy();
	}
}

void Function_Manager::CreateFunction(sf::RenderWindow * w, vector<Event> e, string n)
{
	fm_functions.push_back(Function());
	fm_functions[fm_functions.size() - 1].Init(w, e, n);
}

void Function_Manager::CreateTrigger(Trigger* trig, const string& func_name)
{
	Function* func;
	for (int i = 0; i < fm_functions.size(); i++) {
		if (fm_functions[i].f_name == func_name) {
			func = &fm_functions[i];
			break;
		}
	}
	triggers.insert(make_pair(trig, func));
}

void Function_Manager::StartFunction(string g)
{
	for (int i = 0; i < fm_functions.size(); i++) {
		if (fm_functions[i].f_name == g) {
			fm_functions[i].Start();
			break;
		}
	}
}
