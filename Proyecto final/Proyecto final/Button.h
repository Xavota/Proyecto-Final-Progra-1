#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
class Menu_Manager;
class Game;
using namespace std;
class Button
{
public:
	enum Text_Align {
		left, center, right
	};
public:
	Button();
	Button(sf::Vector2f pos, const string& init_text, Text_Align align, const string& font_name, int CharacterSize);
	~Button();
	void Init(sf::Vector2f pos, const string& init_text, Text_Align align, const string& font_name, int CharacterSize); // Inicializa las variables
	void setEdgeColor(sf::Color edge_color); // Setea el color del borde
	void setTextColor(sf::Color text_color); // Setea el color del texto
	void setFont(string font_name); // Setea la fuente del texto
	void setSize(sf::Vector2f edge_size); // Setea el tamaño del boton
	sf::Vector2f getSize(); // Devuelve el tamaño del boton
	void setPosition(sf::Vector2f pos); // Setea la posición del botón
	sf::Vector2f getPosition(); // Devuelve la posición del botón
	void alignText(Text_Align ta); // Alinea el texto a la izquierda, centrado o a la derecha
	void Update(sf::Time deltaTime); // Cada ciclo
	bool isMouseOver(); // ¿Está el mouse encima? (sin uso por ahora)
	bool isClicked(); // ¿Fue presionado por el mouse? (sin uso por ahora)
	void setActive(bool active); // Activa o desactiva el botón
	//static void onClick(function<void()> f);
	void Render(sf::RenderWindow* window); // Renderiza los elementos del botón
	void Destroy(); // Libera la memoria
private:
	bool btn_active = false;
	sf::RectangleShape btn_edge;
	Text_Align btn_text_align;
public:
	sf::Text btn_text;
	sf::Font btn_text_font;
private:
	Game* game;
};

