#include "NPC.h"

NPC::NPC(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name)
{
	Init(pos, anims, name);
}

NPC::NPC()
{
}

NPC::~NPC()
{
}

void NPC::Init(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name) // Inicializa al NPC como Objeto
{
	Object::Init(pos, anims, name);
}

void NPC::Update(sf::Time deltaTime) // Actualiza al NPC como Objeto
{
	Object::Update(deltaTime);
}

void NPC::handleInputs(sf::Keyboard::Key key, bool isPressed) // Convierte incputs en acciones
{
}

void NPC::Render(sf::RenderWindow * game_window) // Renderiza al NPC como Objeto
{
	Object::Render(game_window);
}

void NPC::Destroy() // Libera la memoria
{
	Object::Destroy();
}

void NPC::move(sf::Vector2f p_move) // Mueve al NPC
{
}
