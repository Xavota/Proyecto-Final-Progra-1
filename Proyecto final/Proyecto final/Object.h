#pragma once
#include <SFML/Graphics.hpp>
#include "Animator_Manager.h"
#include <iostream>
#include <vector>
class Game;
class Object
{
public:
	Object(sf::Vector2f size);
	Object();
	~Object();
	virtual void Init(sf::Vector2f pos);
	virtual void Update(sf::Time deltaTime);
	virtual void Render(sf::RenderWindow* game_window);
	virtual void Destroy();
	virtual void move(sf::Vector2f p_move);
	Animator_Manager& p_Animation();
	sf::RectangleShape p_shape;
	sf::Vector2f o_posAnterior;
protected:
	friend class Function;
	friend class Trigger;
	friend class Game;
	float Speed = 100.f;
	sf::Vector2f p_movement;
	Animator_Manager p_AM;
	Game* game;
private:
	static vector<Object*> objs;
};

