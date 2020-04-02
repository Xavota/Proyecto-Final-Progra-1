#include "Button.h"
#include "Game.h"
#include "Menu_manager.h"

Button::Button()
{
}

Button::Button(sf::Vector2f pos, const string& init_text, Text_Align align = left, const string& font_name = "Fonts/Hijakers.otf", int CharacterSize = 15)
{
	Init(pos, init_text, align, font_name, CharacterSize);
}

Button::~Button()
{
}

void Button::Init(sf::Vector2f pos, const string& init_text, Text_Align align = left, const string& font_name = "Fonts/Hijakers.otf", int CharacterSize = 15)
// Inicializa las variables, algunas ya predeterminadas
{
	game = Game::getInstance();
	btn_text_align = align;
	btn_edge.setFillColor(sf::Color(0, 0, 0, 0));
	btn_edge.setOutlineColor(game->edge_unselected_color);
	btn_edge.setOutlineThickness(4);
	btn_edge.setSize({ btn_text.getGlobalBounds().width + 10.f, btn_text.getGlobalBounds().height + 10.f });
	btn_edge.setPosition(pos);
	btn_text.setPosition(btn_edge.getPosition() + sf::Vector2f(-5.f, -5.f));
	btn_text_font.loadFromFile(font_name);
	btn_text.setFont(btn_text_font);
	btn_text.setCharacterSize(CharacterSize);
	btn_text.setString(init_text);
	btn_text.setFillColor(game->text_color);
}

void Button::setEdgeColor(sf::Color edge_color) // Setea el color del borde
{
	btn_edge.setOutlineColor(edge_color);
}

void Button::setTextColor(sf::Color text_color) // Setea el color del texto
{
	btn_text.setFillColor(text_color);
}

void Button::setFont(string font_name) // Setea la fuente del texto
{
	btn_text_font.loadFromFile(font_name);
	btn_text.setFont(btn_text_font);
}

void Button::setSize(sf::Vector2f edge_size) // Setea el tamaño del boton
{
	btn_edge.setSize(edge_size);
}

sf::Vector2f Button::getSize() // Devuelve el tamaño del borde del botón
{
	return btn_edge.getSize();
}

void Button::setPosition(sf::Vector2f pos) // Setea la posición del botón
{
	btn_edge.setPosition(pos);
}

sf::Vector2f Button::getPosition() // Devuelve la posición del botón
{
	return btn_edge.getPosition();
}

void Button::alignText(Text_Align text_aling) // Setea la alineación del texto
{
	btn_text_align = text_aling;
}

void Button::Update(sf::Time deltaTime) // Cada ciclo
{
	btn_text.setFont(btn_text_font);
	switch (btn_text_align) { // Alinea el texto según el enumerador
	case Text_Align::left:
		btn_text.setPosition(sf::Vector2f(btn_edge.getPosition().x + 5.f, btn_edge.getPosition().y + btn_edge.getSize().y / 2 - btn_text.getGlobalBounds().height / 2));
		break;
	case Text_Align::center:
		btn_text.setPosition(sf::Vector2f(btn_edge.getPosition().x + btn_edge.getSize().x / 2 - btn_text.getGlobalBounds().width / 2, btn_edge.getPosition().y + btn_edge.getSize().y / 2 - btn_text.getGlobalBounds().height / 2));
		break;
	case Text_Align::right:
		btn_text.setPosition(sf::Vector2f(btn_edge.getPosition().x + btn_edge.getSize().x - btn_text.getGlobalBounds().width - 5.f, btn_edge.getPosition().y + btn_edge.getSize().y / 2 - btn_text.getGlobalBounds().height / 2));
		break;
	}
}

bool Button::isMouseOver() // ¿El mouse está encima? (sin uso por ahora)
{
	return false;
}

bool Button::isClicked() // ¿Fue presionado por el mouse? (sin uso por ahora)
{
	return false;
}

void Button::setActive(bool active) // Activa o desactiva el botón
{
	btn_active = active;
}

/*void Button::onClick(function<void()> f)
{
	f();
}*/

void Button::Render(sf::RenderWindow * window) // Renderiza los elementos del botón
{
	if (btn_active) {
		window->draw(btn_edge);
		btn_text.setFont(btn_text_font);
		window->draw(btn_text);
	}
}

void Button::Destroy() // Limpia la memoria
{
	if (game != nullptr) {
		game = nullptr;
	}
}
