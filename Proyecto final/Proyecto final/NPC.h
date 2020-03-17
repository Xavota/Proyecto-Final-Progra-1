#pragma once
#include "Object.h"
class NPC : public Object
{
public:
	NPC(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name);
	NPC();
	~NPC();
	void Init(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name);
	void Update(sf::Time deltaTime);
	void handleInputs(sf::Keyboard::Key key, bool isPressed);
	void Render(sf::RenderWindow* game_window);
	void Destroy();
	void move(sf::Vector2f p_move);
};

