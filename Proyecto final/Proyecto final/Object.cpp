#include "Object.h"
#include "Game.h"

vector<Object*> Object::objs = {};
Object::Object(sf::Vector2f size) : p_shape(size)
{
	objs.push_back(this);
}

Object::Object()
{
	objs.push_back(this);
}


Object::~Object()
{
}

void Object::Init(sf::Vector2f pos)
{
	game = Game::getInstance();
	p_shape.setPosition(pos * 64.f);
	o_posAnterior = p_shape.getPosition();
}

void Object::Update(sf::Time deltaTime)
{
	p_shape.move(p_movement);
	if (p_movement == sf::Vector2f(0.f, 0.f)) {
		p_AM.SetState(p_AM.getState() == "arriba" || p_AM.getState() == "idle_arriba" ? "idle_arriba" : 
			(p_AM.getState() == "abajo" || p_AM.getState() == "idle_abajo" ? "idle_abajo" : 
			(p_AM.getState() == "izquierda" || p_AM.getState() == "idle_izquierda" ? "idle_izquierda" :  "idle_derecha")));
	}
	p_AM.Update(deltaTime);
	for (int i = 0; i < objs.size(); i++) {
		if (objs[i]->p_shape.getGlobalBounds().intersects(this->p_shape.getGlobalBounds()) && objs[i] != this) {
			objs[i]->p_shape.setPosition(objs[i]->o_posAnterior);
			this->p_shape.setPosition(this->o_posAnterior);
		}
	}
	o_posAnterior = p_shape.getPosition();
}

void Object::Render(sf::RenderWindow * game_window)
{
	game_window->draw(p_shape);
}

void Object::Destroy()
{
}

void Object::move(sf::Vector2f p_move)
{
}

Animator_Manager& Object::p_Animation()
{
	return p_AM;
}
