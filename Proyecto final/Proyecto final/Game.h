#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Player.h"
#include "Function.h"
#include "Function_Manager.h"
#include "NPC.h"
#include "Map_Manager.h"
#include "Pause_Menu.h"
using namespace std;
class Game
{
public:
	static Game* getInstance(); // Pasa la instancia del singleton
	void run(); // Empieza el juego
	void Init(); // Inicializa las variables del juego
	void Destroy(); // Libera la memoria
	float pixels = 32.f; // La resolución del juego
	bool pause = false; // En pausa
	sf::Color box_color = sf::Color(255, 50, 50, 255);                                                                                       // Los colores
	sf::Color edge_color = sf::Color::White, edge_unselected_color = sf::Color(220, 220, 220, 255), edge_selected_color = sf::Color::White;  // de las
	sf::Color text_color = sf::Color::White, text_selected_color = sf::Color::Black;                                                         // interfaces
private:
	static Game* instance; // La instancia del singleton
	Game();
	void processEvents(); // Procesa los eventos del juego
	void update(sf::Time deltaTime); // Cada ciclo del juego
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); // Convierte los inputs en acciones
	void Save(int file); // Guarda el juego
	void Load(int file); // Carga el juego
	void render(); // Renderiza los objetos del juego
private:
	friend class Function;
	friend class Object;
	friend class Player;
	friend class Map;
	friend class Map_Manager;
	friend class Trigger;
	friend class Pause_Menu;
	sf::RenderWindow mWindow;
	bool escPressed = false, keyPressed = false;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // Limita la cantidad de ciclos por segundo
public:
private:
	Player* g_player;
	Map_Manager mm;
	Pause_Menu pm;
};