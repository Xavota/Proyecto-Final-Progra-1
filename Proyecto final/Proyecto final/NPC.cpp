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

void NPC::Init(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name)
{
	Object::Init(pos, anims, name);
}

void NPC::Update(sf::Time deltaTime)
{
	Object::Update(deltaTime);
}

void NPC::handleInputs(sf::Keyboard::Key key, bool isPressed)
{
}

void NPC::Render(sf::RenderWindow * game_window)
{
	Object::Render(game_window);
}

void NPC::Destroy()
{
	Object::Destroy();
}

void NPC::move(sf::Vector2f p_move)
{
}
