#pragma once
#include <SFML/Graphics.hpp>
#include "Animator_Manager.h"
#include <iostream>
#include <vector>
class Game;
class Object
{
public:
	Object(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name);
	Object();
	~Object();
	virtual void Init(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name);
	virtual void Update(sf::Time deltaTime);
	virtual void handleInputs(sf::Keyboard::Key key, bool isPressed);
	void SetState(string anim);
	void SetState(Animator_Manager::Animation anim);
	void SetState(Animator_Manager::AnimationTypes anim_type, Animator_Manager::AnimationFace anim_face);
	void SetState(Animator_Manager::AnimationTypes anim_type);
	void SetState(Animator_Manager::AnimationFace anim_face);
	virtual void Render(sf::RenderWindow* game_window);
	virtual void Destroy();
	virtual void move(sf::Vector2f p_move);
	static Object * getObject(string name);
	Animator_Manager& p_Animation();
	sf::RectangleShape p_shape;
protected:
	friend class Function;
	friend class Trigger;
	friend class Game;
	friend class Map;
	float Speed = 100.f;
	sf::Vector2f o_posAnterior;
	sf::Vector2f p_movement;
	Animator_Manager p_AM;
	string o_name;
	Game* game;
private:
	static vector<Object*> objs;
};

