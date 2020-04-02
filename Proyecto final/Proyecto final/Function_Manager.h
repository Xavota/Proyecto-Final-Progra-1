#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Function.h"
#include "Trigger.h"
class Function_Manager // El que controla las funciones para que se ejecuten
{
public:
	class Trigger_Pair { // Sustituye al map, porque me daba problemas
	public:
		Trigger_Pair(Trigger t, Function f) { trig = t; func = f; };
		Trigger trig;
		Function func;
	};
	Function_Manager();
	~Function_Manager();
	void Init(); // Inicializa las variables
	void Update(sf::Time deltaTime); // Cada ciclo
	void Render(sf::RenderWindow* window); // Renderiza lo necesario para las funciones
	void Destroy(); // Limpia la memoria
	void handleInputs(sf::Keyboard::Key key, bool isPressed); // Convierte inputs en acciones
	void CreateFunction(Trigger trig, Function func); // Crea una funció y le asigna un trigger con el que se va a ejecutar
private:
	//vector<Function> fm_functions;
	//map<Trigger, Function> triggers;
	//map<Trigger, Function>::iterator trigsIt;
	vector<Trigger_Pair> triggers;
	//void StartFunction(string g);
};

