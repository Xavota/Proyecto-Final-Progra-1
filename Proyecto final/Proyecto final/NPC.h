#pragma once
#include "Object.h"
class NPC : public Object
{
public:
	NPC(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name);
	NPC();
	~NPC();
	void Init(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name); // Inicializa las variables
	void Update(sf::Time deltaTime); // Cada ciclo
	void handleInputs(sf::Keyboard::Key key, bool isPressed); // Convierte inputs en acciones
	void Render(sf::RenderWindow* game_window); // Renderiza el npc
	void Destroy(); // Limpia la memoria
	void move(sf::Vector2f p_move); // Mueve al npc
};

