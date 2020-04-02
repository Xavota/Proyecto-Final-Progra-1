#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Map.h";
class Game;
using namespace std;
class Trigger
{
public:
	enum triggers {
		on_trigger_enter, on_triger_exit, on_trigger_stay, on_key_pressed, on_key_released, on_key, on_interact, on_pos_interact, on_map_enter
	};
	Trigger();
	~Trigger();
	void Init(); // Inicializa las variables
	void Update(sf::Time deltaTime); // Cada ciclo
	void Render(sf::RenderWindow* window); // Renderiza los objetos
	void Destory(); // Limpia la memoria
	void handleInputs(sf::Keyboard::Key key, bool isPressed); // Convierte los inputs en acciones
	bool TriggerIsMet(); // ¿El input se cumple?
	static Trigger onTriggerEnter(sf::Vector2i init, sf::Vector2i fin); // Devuelve un trigger con la etiqueta "on triger enter"
	static Trigger onTriggerExit(sf::Vector2i init, sf::Vector2i fin); // Devuelve un trigger con la etiqueta "on triger exit"
	static Trigger onTriggerStay(sf::Vector2i init, sf::Vector2i fin); // Devuelve un trigger con la etiqueta "on triger stay"
	static Trigger onKeyPressed(); // Devuelve un trigger con la etiqueta "on key pressed"
	static Trigger onKeyReleased(); // Devuelve un trigger con la etiqueta "on key released"
	static Trigger onKey(); // Devuelve un trigger con la etiqueta "on key"
	static Trigger onInteract(Object* interactuable); // Devuelve un trigger con la etiqueta "on interact"
	static Trigger onInteract(sf::Vector2i pos); // Devuelve un trigger con la etiqueta "on pos interact"
	static Trigger onMapEnter(Map* map); // Devuelve un trigger con la etiqueta "on map enter"
private:
	bool inside = false;
	bool EnterPressed = false, key_pressed = false;
	bool onMap = false;
	triggers type;
	sf::RectangleShape t_zones;
	sf::Vector2f t_pos_interractuable;
private:
	Player* g_player;
	Object* t_Interactuable;
	Map* t_map;
	static Game* game;
};

