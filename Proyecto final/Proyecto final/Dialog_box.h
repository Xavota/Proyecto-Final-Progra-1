#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
using namespace std;
class Dialog_box
{
public:
	static Dialog_box* getInstance(); // Devuelve la instancia del singleton
	~Dialog_box();
	void setBoxColor(sf::Color box_color); // Le pone color a la caja, por si quieres cambiarlo
	void setEdgeColor(sf::Color edge_color); // Le pone color al borde, por si quieres cambiarlo
	void setTextColor(sf::Color text_color); // Le pone color al texto, por si quieres cambiarlo
	void setTextFont(const string& text_font_file); // Le pone la fuente al texto, por si quieres cambiarlo
	void setTexSize(int text_size); // Le pone color al borde, por si quieres cambiarlo
	void setTextVelocity(float text_velocity); // Le pone velocidad al texto, por si quieres cambiarlo
	void setActive(bool active); // Activa o desactiva la caja
	void Write(const string& text); // Empieza a escribir el texto indicado
	//void Init(sf::RenderWindow * window, sf::Color box_color, sf::Color edge_color, sf::Color text_color, const string& text_font_file, int text_size, float text_velocity);
	void Init(sf::RenderWindow * window, sf::Color box_color, sf::Color edge_color, sf::Color text_color, float text_velocity); // Inicializa las variables
	void Update(sf::Time deltaTime); // Cada cilco
	string AdjustText(string s); // Ajusta el texto, para que se mantenga dentro del cuadro
	void Render(sf::RenderWindow* window); // Renderiza los elementos del cuadro de texto
	void Destroy(); // Limpia la memoria
private:
	static Dialog_box* instance;
	Dialog_box();
	sf::RectangleShape db_Rectangle;
	sf::Vector2f db_Normal_Size;
	sf::Color db_box_color, db_edge_color, db_text_color;
	vector<sf::RectangleShape> db_edge{ sf::RectangleShape(), sf::RectangleShape(), sf::RectangleShape(), sf::RectangleShape() };
	sf::Text db_text;
	sf::Font db_text_font;
	sf::RenderWindow * db_game_window;
	float db_text_velocity = 0, Time = 0, db_y_size = 0;
	string db_text_text;
	bool db_active = false, db_writing = false;
	int letter = 0;
};

