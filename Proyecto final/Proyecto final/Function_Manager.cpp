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
	bool inFunc = false;
	/*for (int i = 0; i < fm_functions.size(); i++) {
		fm_functions[i].Update(deltaTime);
		if (fm_functions[i].f_Active)
			inFunc = true;
	}
	for (trigsIt = triggers.begin(); trigsIt != triggers.end(); trigsIt++) {
		trigsIt->first.Update(deltaTime);
		if (trigsIt->first.TriggerIsMet() && !inFunc) {
			trigsIt->second.Start();
		}
	}*/
	for (Trigger_Pair& trig : triggers) {
		trig.func.Update(deltaTime);
		if (trig.func.f_Active) {
			inFunc = true;
		}
		trig.trig.Update(deltaTime);
		if (trig.trig.TriggerIsMet() && !inFunc) {
			trig.func.Start();
		}
	}
}

void Function_Manager::handleInputs(sf::Keyboard::Key key, bool isPressed)
{
	/*for (int i = 0; i < fm_functions.size(); i++) {
		fm_functions[i].handleInputs(key, isPressed);
	}
	for (trigsIt = triggers.begin(); trigsIt != triggers.end(); trigsIt++) {
		trigsIt->first.handleInputs(key, isPressed);
	}*/
	for (Trigger_Pair& trig : triggers) {
		trig.func.handleInputs(key, isPressed);
		trig.trig.handleInputs(key, isPressed);
	}
}

void Function_Manager::Render(sf::RenderWindow * window)
{
	/*for (trigsIt = triggers.begin(); trigsIt != triggers.end(); trigsIt++) {
		trigsIt->first->Render(window);
	}
	for (int i = 0; i < fm_functions.size(); i++) {
		fm_functions[i].Render(window);
	}*/
	for (Trigger_Pair& trig : triggers) {
		trig.func.Render(window);
		trig.trig.Render(window);
	}
}

void Function_Manager::Destroy()
{
	/*for (trigsIt = triggers.begin(); trigsIt != triggers.end(); trigsIt++) {
		trigsIt->first->Destory();
	}
	for (int i = 0; i < fm_functions.size(); i++) {
		fm_functions[i].Destroy();
	}*/
	for (Trigger_Pair& trig : triggers) {
		trig.func.Destroy();
		trig.trig.Destory();
	}
}

void Function_Manager::CreateFunction(Trigger trig, Function func)
{
	/*triggers.push_back(Function());
	fm_functions[fm_functions.size() - 1].Init(w, e, n);*/
	triggers.push_back(Trigger_Pair{ trig, func });
}