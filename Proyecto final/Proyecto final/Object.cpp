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

void Object::Init(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name) // Inicializa las variables necesarias
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

void Object::Update(sf::Time deltaTime) // Cada ciclo
{
	p_shape.move(p_movement); // Mueve el objeto
	if (p_movement == sf::Vector2f(0.f, 0.f)) { // Si la velocidad es 0 pone la animación del tipo idle según su posición
		p_AM.SetState(Animator_Manager::AnimationTypes::idle);
	}
	p_AM.Update(deltaTime);
	vector<Map*> maps = game->mm.maps();
	for (int i = 0; i < maps.size(); i++) { // Por cada mapa
		if (maps[i]->isActive()) { // Si el mapa está activo
			for (int j = 0; j < maps[i]->map_layers.size(); j++) { // Por cada layer del mapa
				if (maps[i]->map_layers[j].l_layer == 2) { // Si la leyer es de nivel 2 (a nivel de jugador)
					for (vector<sf::RectangleShape> z : maps[i]->map_tiles_grids[j]) { // Detecta las coliciones con los tiles
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
			{ // Si el jugador se sale de los límites del mapa lo detiene
				this->p_shape.setPosition(this->o_posAnterior);
			}
			for (NPC* npc : maps[i]->map_npcs) { // Coliciones con npcs
				if (npc->p_shape.getGlobalBounds().intersects(this->p_shape.getGlobalBounds())) {
					this->p_shape.setPosition(this->o_posAnterior);
				}
			}
			for (Object* obj : maps[i]->map_objs) { // Coliciones con objetos
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

void Object::SetState(string anim) // Setea el estado del jugador con el nombre
{
	p_AM.SetState(anim);
}

void Object::SetState(Animator_Manager::Animation anim) // Setea el estado del jugador con la animación
{
	p_AM.SetState(anim);
}

void Object::SetState(Animator_Manager::AnimationTypes anim_type, Animator_Manager::AnimationFace anim_face) // Setea el estado del jugador con el tipo y la dirección
{
	p_AM.SetState(anim_type, anim_face);
}

void Object::SetState(Animator_Manager::AnimationTypes anim_type) // Setea el estado del jugador con tipo
{
	p_AM.SetState(anim_type);
}

void Object::SetState(Animator_Manager::AnimationFace anim_face) // Setea el estado del jugador con la dirección
{
	p_AM.SetState(anim_face);
}

void Object::Render(sf::RenderWindow * game_window) // Renderiza al objeto
{
	game_window->draw(p_shape);
}

void Object::Destroy() // Limpia la memoria
{
	if (game != nullptr) {
		game = nullptr;
	}
	for (Object* obj : objs) {
		if (obj != nullptr) {
			obj = nullptr;
		}
	}
}

void Object::move(sf::Vector2f p_move) // Mueve al objeto
{
}

Object * Object::getObject(string name) // Regresa un objeto de la lista por su nombre
{
	for (Object* obj : objs) {
		if (obj->o_name == name)
			return obj;
	}
	return nullptr;
}

Animator_Manager& Object::p_Animation() // Regresa la animación actual
{
	return p_AM;
}
