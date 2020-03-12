#include "Object.h"
#include "Game.h"
#include "Map.h"

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
	p_shape.setPosition(pos * game->pixels);
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
	vector<Map*> maps = game->mm.maps();
	for (int i = 0; i < maps.size(); i++) {
		if (maps[i]->isActive()) {
			for (int j = 0; j < maps[i]->map_layers.size(); j++) {
				if (maps[i]->map_layers[j].l_layer == 2) {
					for (vector<sf::RectangleShape> z : maps[i]->map_tiles_grids[j]) {
						for (sf::RectangleShape y : z) {
							if (y.getGlobalBounds().intersects(this->p_shape.getGlobalBounds())) {
								this->p_shape.setPosition(this->o_posAnterior);
							}
						}
					}
				}
			}
			if (this->p_shape.getPosition().x <= 0 || this->p_shape.getPosition().x + this->p_shape.getSize().x >= maps[i]->map_size.x * game->pixels
				|| this->p_shape.getPosition().y <= 0 || this->p_shape.getPosition().y + this->p_shape.getSize().y >= maps[i]->map_size.y * game->pixels)
			{
				this->p_shape.setPosition(this->o_posAnterior);
			}
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
