#include "Button_Manager.h"
#include "Game.h"

Button_Manager::Button_Manager()
{
	//Button::onClick(&Button_Manager::a);
}

Button_Manager::~Button_Manager()
{
}

void Button_Manager::Init() // Inicializa el botón
{
	game = Game::getInstance();
	bm_selector.setFillColor(sf::Color::Transparent);
	bm_selector.setOutlineThickness(4);
	bm_selector.setOutlineColor(game->edge_selected_color);
}

void Button_Manager::AddButton(Button btn) // Agrega un botón a la lista
{
	bm_btns.push_back(btn);
}

int Button_Manager::Update(sf::Time deltaTime) // Cada ciclo
{
	if (bm_prev) { // Si presionas atrás o arriba mueve el selector al botón anterior
		bm_prev = false;
		bm_seleccion = (bm_seleccion + bm_btns.size() - 1) % bm_btns.size();
	}
	if (bm_next) { // Si presionas adelante o abajo, mueve el selector al botón siguiente
		bm_next = false;
		bm_seleccion = (bm_seleccion + 1) % bm_btns.size();
	}
	for (Button& btn : bm_btns) { // Activa o desactiva a todos los botones, según sea el caso
		btn.setActive(bm_active);
	}
	bm_selector.setPosition(bm_btns[bm_seleccion].getPosition()); // Pone el selector en el botón seleccionado
	bm_selector.setSize(bm_btns[bm_seleccion].getSize()); // Y le pone el tamaño de ese botón
	for (int i = 0; i < bm_btns.size(); i++) {
		bm_btns[i].setTextColor(i == bm_seleccion ? game->text_selected_color : game->text_color); // Cambia el color del texto según si está seleccionado o no
	}
	if (bm_enter) { // Si presionas enter devuelve el valor del botón seleccionado actual (provicional)
		bm_enter = false;
		return bm_seleccion;
	}
	return -1;
}

void Button_Manager::SetActive(bool active) // Activa o desactiva los botones
{
	bm_active = active;
}

void Button_Manager::handleInputs(sf::Keyboard::Key key, bool isPressed) // Combierte los inputs en acciones
{
	if (bm_active) { 
		if (key == sf::Keyboard::Up || key == sf::Keyboard::Left || key == sf::Keyboard::W || key == sf::Keyboard::A) {
			if (!pressed) {
				pressed = isPressed;
				bm_prev = isPressed;
			}
			else {
				pressed = isPressed;
			}
		}
		if (key == sf::Keyboard::Down || key == sf::Keyboard::Right || key == sf::Keyboard::S || key == sf::Keyboard::D) {
			if (!pressed) {
				pressed = isPressed;
				bm_next = isPressed;
			}
			else {
				pressed = isPressed;
			}
		}
		if (key == sf::Keyboard::Return) {
			if (!pressed) {
				pressed = isPressed;
				bm_enter = isPressed;
			}
			else {
				pressed = isPressed;
			}
		}
	}
}

void Button_Manager::Render(sf::RenderWindow * window) // Renderiza los botones
{
	if (bm_active) {
		for (Button& btn : bm_btns) {
			btn.Render(window);
		}
		window->draw(bm_selector);
	}
}

void Button_Manager::Destroy() // Libera memoria
{
	if (game != nullptr) {
		game = nullptr;
	}
	for (Button btn : bm_btns) {
		btn.Destroy();
	}
}