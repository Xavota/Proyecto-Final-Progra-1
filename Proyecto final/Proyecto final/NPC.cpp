#include "NPC.h"



NPC::NPC(sf::Vector2f size)
{
	p_shape.setSize(size);
}

NPC::NPC()
{
}


NPC::~NPC()
{
}

void NPC::Init(sf::Vector2f pos)
{
	Object::Init(pos);
}

void NPC::Update(sf::Time deltaTime)
{
	Object::Update(deltaTime);
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
