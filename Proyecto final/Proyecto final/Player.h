#pragma once
#include "Object.h"
class Player : public Object
{
public:
	Player(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name);
	Player(const Player& p) { *this = p; };
	~Player();
	void Init(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name);
	void Update(sf::Time deltaTime);
	void handleInputs(sf::Keyboard::Key key, bool isPressed);
	void Render(sf::RenderWindow* game_window);
	void Destroy();
	void move(sf::Vector2f p_move);
private:
	friend class Game;
	bool mIsMovingUp = false, mIsMovingDown = false, mIsMovingLeft = false, mIsMovingRight = false;
};

