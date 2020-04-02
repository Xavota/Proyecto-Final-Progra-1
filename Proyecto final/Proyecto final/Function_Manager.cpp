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

void Function_Manager::Update(sf::Time deltaTime) // Cada ciclo
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
	for (Trigger_Pair& trig : triggers) { // Hace los updates de cada función
		trig.func.Update(deltaTime);
		if (trig.func.f_Active) { // Detecta si alguna está activa
			inFunc = true;
		}
	}
	for (Trigger_Pair& trig : triggers) { // Hace los updates de cada trigger
		trig.trig.Update(deltaTime);
		if (trig.trig.TriggerIsMet() && !inFunc) { // Detecta si algún trigger se cumple para activar su función
			trig.func.Start();
		}
	}
}

void Function_Manager::handleInputs(sf::Keyboard::Key key, bool isPressed) // Convierte los inputs en acciones
{
	/*for (int i = 0; i < fm_functions.size(); i++) {
		fm_functions[i].handleInputs(key, isPressed);
	}
	for (trigsIt = triggers.begin(); trigsIt != triggers.end(); trigsIt++) {
		trigsIt->first.handleInputs(key, isPressed);
	}*/
	for (Trigger_Pair& trig : triggers) { // Llama a los handleInputs de las funciones y triggers
		trig.func.handleInputs(key, isPressed);
		trig.trig.handleInputs(key, isPressed);
	}
}

void Function_Manager::Render(sf::RenderWindow * window) // Renderiza las funciones y los triggers
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

void Function_Manager::Destroy() // Limpia la memoria
{
	/*for (trigsIt = triggers.begin(); trigsIt != triggers.end(); trigsIt++) {
		trigsIt->first->Destory();
	}
	for (int i = 0; i < fm_functions.size(); i++) {
		fm_functions[i].Destroy();
	}*/
	for (Trigger_Pair& trig : triggers) { // Destruye los triggers y las funciones
		trig.func.Destroy();
		trig.trig.Destory();
	}
}

void Function_Manager::CreateFunction(Trigger trig, Function func) // Agrega un trigger y su función
{
	/*triggers.push_back(Function());
	fm_functions[fm_functions.size() - 1].Init(w, e, n);*/
	triggers.push_back(Trigger_Pair{ trig, func });
}