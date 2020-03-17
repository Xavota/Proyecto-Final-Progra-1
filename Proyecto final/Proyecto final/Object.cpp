#include "Object.h"
#include "Game.h"
#include "Map.h"

vector<Object*> Object::objs = {};
Object::Object(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name)
{
	objs.push_back(this);
	Init(pos, anims, name);
}

Object::Object()
{
	objs.push_back(this);
}


Object::~Object()
{
}

void Object::Init(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name)
{
	game = Game::getInstance();
	p_shape.setPosition(pos * game->pixels);
	p_shape.setSize({ game->pixels, game->pixels });
	o_posAnterior = p_shape.getPosition();
	p_AM.Init(p_shape);
	for (Animator_Manager::Animation a : anims) {
		p_AM.setAnimation(a);
	}
	p_AM.SetState(Animator_Manager::AnimationTypes::idle, Animator_Manager::AnimationFace::down);
	o_name = name;
}

void Object::Update(sf::Time deltaTime)
{
	p_shape.move(p_movement);
	if (p_movement == sf::Vector2f(0.f, 0.f)) {
		Animator_Manager::Animation a = p_AM.getAnimation(p_AM.getState());
		p_AM.SetState(a.a_face == Animator_Manager::AnimationFace::up ? p_AM.getAnimation(Animator_Manager::AnimationTypes::idle, Animator_Manager::AnimationFace::up) :
			(a.a_face == Animator_Manager::AnimationFace::down ? p_AM.getAnimation(Animator_Manager::AnimationTypes::idle, Animator_Manager::AnimationFace::down) :
			(a.a_face == Animator_Manager::AnimationFace::left ? p_AM.getAnimation(Animator_Manager::AnimationTypes::idle, Animator_Manager::AnimationFace::left) :
				(a.a_face == Animator_Manager::AnimationFace::right ? p_AM.getAnimation(Animator_Manager::AnimationTypes::idle, Animator_Manager::AnimationFace::right) : p_AM.getAnimation()))));
		
	}
	p_AM.Update(deltaTime);
	/*for (int i = 0; i < objs.size(); i++) {
		if (objs[i]->p_shape.getGlobalBounds().intersects(this->p_shape.getGlobalBounds()) && objs[i] != this) {
			objs[i]->p_shape.setPosition(objs[i]->o_posAnterior);
			this->p_shape.setPosition(this->o_posAnterior);
		}
	}*/
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
			if (this->p_shape.getPosition().x < 0 || this->p_shape.getPosition().x + this->p_shape.getSize().x > maps[i]->map_size.x * game->pixels
				|| this->p_shape.getPosition().y < 0 || this->p_shape.getPosition().y + this->p_shape.getSize().y > maps[i]->map_size.y * game->pixels)
			{
				this->p_shape.setPosition(this->o_posAnterior);
			}
			for (NPC* npc : maps[i]->map_npcs) {
				if (npc->p_shape.getGlobalBounds().intersects(this->p_shape.getGlobalBounds())) {
					this->p_shape.setPosition(this->o_posAnterior);
				}
			}
			for (Object* obj : maps[i]->map_objs) {
				if (obj->p_shape.getGlobalBounds().intersects(this->p_shape.getGlobalBounds())) {
					this->p_shape.setPosition(this->o_posAnterior);
				}
			}
		}
	}
	o_posAnterior = p_shape.getPosition();
}

void Object::handleInputs(sf::Keyboard::Key key, bool isPressed)
{
}

void Object::SetState(string anim)
{
	p_AM.SetState(anim);
}

void Object::SetState(Animator_Manager::Animation anim)
{
	p_AM.SetState(anim);
}

void Object::SetState(Animator_Manager::AnimationTypes anim_type, Animator_Manager::AnimationFace anim_face)
{
	p_AM.SetState(anim_type, anim_face);
}

void Object::SetState(Animator_Manager::AnimationTypes anim_type)
{
	p_AM.SetState(anim_type);
}

void Object::SetState(Animator_Manager::AnimationFace anim_face)
{
	p_AM.SetState(anim_face);
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

Object * Object::getObject(string name)
{
	for (Object* obj : objs) {
		if (obj->o_name == name)
			return obj;
	}
	return nullptr;
}

Animator_Manager& Object::p_Animation()
{
	return p_AM;
}
