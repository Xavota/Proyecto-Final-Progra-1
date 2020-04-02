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
	virtual void Init(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name); // Inicializa las variables
	virtual void Update(sf::Time deltaTime); // Cada ciclo
	virtual void handleInputs(sf::Keyboard::Key key, bool isPressed); // Convierte inputs en acciones
	void SetState(string anim); // Setea el estado del objeto por nombre
	void SetState(Animator_Manager::Animation anim); // Setea el estado del objeto por animación
	void SetState(Animator_Manager::AnimationTypes anim_type, Animator_Manager::AnimationFace anim_face); // Setea el estado del objeto por tipo y dirección
	void SetState(Animator_Manager::AnimationTypes anim_type); // Setea el estado del objeto por tipo
	void SetState(Animator_Manager::AnimationFace anim_face); // Setea el estado del objeto por dirección
	virtual void Render(sf::RenderWindow* game_window); // Renderiza el objeto
	virtual void Destroy(); // Libera la memoria
	virtual void move(sf::Vector2f p_move); // Mueve al objeto
	static Object * getObject(string name); // Devuelve el objeto por su nombre de la lista estática de objetos
	Animator_Manager& p_Animation(); // Devuelve el Animator Manager con la animación actial
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

