#pragma once
#include "Object.h"
class NPC : public Object
{
public:
	NPC(sf::Vector2f size);
	NPC();
	~NPC();
	void Init(sf::Vector2f pos);
	void Update(sf::Time deltaTime);
	void Render(sf::RenderWindow* game_window);
	void Destroy();
	void move(sf::Vector2f p_move);
};

