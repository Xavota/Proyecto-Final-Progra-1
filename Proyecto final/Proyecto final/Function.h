#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "Event.h"
#include "Dialog_box.h"
#include "Player.h"
#include "Map_Manager.h"
#include "s_string.h"
class Game;
class Function
{
public:
	Function();
	Function(string func_file_name);
	~Function();
	void Start(); // Inicia la fucnión
	void handleInputs(sf::Keyboard::Key key, bool isPressed); // Convierte inputs en acciones
	void Init(string func_file_name); // Inicializa las variables
	void Update(sf::Time deltaTime); // Cada ciclo
	void Render(sf::RenderWindow* w); // Renderiza lo necesario para las funciones
	void Destroy(); // Limpia la memoria
private:
	friend class Function_Manager;
	void TextBox(string text); // Escribir en la caja de texto
	void setSpeed(float speed, Object* player); // Setea la velocidad de un objeto
	void GoToMap(const string& map_name, sf::Vector2i pos); // Te lleva a un mapa en una ubicación específica
	void Win(); // Ganas el juego
private:
	int f_nEvent = 0;
	bool f_Active = false, f_working = false, EnterPressed = false, key_pressed = false;
	string f_name;
private:
	Game* game;
	Dialog_box* f_dialogBox;
	vector<Event> events;
};
istream& operator>>(istream& is, sf::Vector2i& v); // Operador sobrecargado para leer vector2i
