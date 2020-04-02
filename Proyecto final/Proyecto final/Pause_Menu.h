#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button_Manager.h"
using namespace std;
class Game;
class Pause_Menu
{
public:
	Pause_Menu();
	~Pause_Menu();
	void Init(sf::RenderWindow* window); // Inicializa las variables
	void Update(sf::Time deltaTime); // Cada ciclo
	void handleInputs(sf::Keyboard::Key key, bool ispressed); // Convierte los inputs en acciones
	void Render(sf::RenderWindow* window); // Renderiza el menu
	void Destroy(); // Libera la memoria
private:
	sf::RectangleShape pm_box, pm_money_box;
	sf::RectangleShape pm_edge, pm_selection, pm_money_edge;
	//vector<sf::RectangleShape> pm_texts_edge;
	//vector<sf::Text> pm_texts;
	//vector<Button> pm_buttons;
	Button_Manager pm_bm;
	sf::Font pm_texts_font;
	sf::Text pm_money_text;
	sf::Color pm_box_color, pm_edge_color, pm_text_color;
	sf::RenderWindow* pm_window;
	float pm_texts_height = 0;
private:
	Game* game;
};

