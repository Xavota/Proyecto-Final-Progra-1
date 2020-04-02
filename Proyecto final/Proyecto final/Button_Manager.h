#pragma once
#include "Button.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
class Game;
using namespace std;
class Button_Manager // Maneja los botones
{
public:
	Button_Manager();
	~Button_Manager();
	void Init(); // Inicializa las variables
	void AddButton(Button btn); // Agrega un boton
	int Update(sf::Time deltaTime); // Cada ciclo. Devuelve el valor del botón presionado (provicional)
	void SetActive(bool active); // Activa o desactiva los botones
	void handleInputs(sf::Keyboard::Key key, bool isPressed); // Convierte los inputs en acciones
	void Render(sf::RenderWindow* window); // Renderiza los botones
	void Destroy(); // Libera la memoria
public:
	sf::RectangleShape bm_selector;
	int bm_seleccion = 0;
	bool bm_active = false;
	bool bm_next = false, bm_prev = false, bm_enter = false, pressed = false;
public:
	Game* game;
	vector<Button> bm_btns;
};

