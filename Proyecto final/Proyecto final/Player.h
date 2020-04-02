#pragma once
#include "Object.h"
class Player : public Object // El jugador
{
public:
	Player(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name);
	Player(const Player& p) { *this = p; };
	~Player();
	void Init(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name); // Inicializa las variables
	void Update(sf::Time deltaTime); // Cada ciclo
	void handleInputs(sf::Keyboard::Key key, bool isPressed); // Convierte inputs en acciones
	void Render(sf::RenderWindow* game_window); // Renderiza al jugador
	void Destroy(); // Libera la memoria
	void move(sf::Vector2f p_move); // Mueve al jugador
private:
	friend class Game;
	friend class Pause_Menu;
	bool mIsMovingUp = false, mIsMovingDown = false, mIsMovingLeft = false, mIsMovingRight = false;
	int p_money = 0;
};

