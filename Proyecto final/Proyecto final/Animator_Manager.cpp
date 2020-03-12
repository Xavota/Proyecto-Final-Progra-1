#include "Animator_Manager.h"



Animator_Manager::Animator_Manager()
{
}


Animator_Manager::~Animator_Manager()
{
}

void Animator_Manager::setAnimation(vector<sf::Vector2u> coords, string name, AnimationTypes am_type)
{
	AM_Animations.push_back(Animation{ coords, name, am_type });
}

void Animator_Manager::SetState(const string& a)
{
	for (AM_AnimIt = AM_Animations.begin(); AM_AnimIt != AM_Animations.end(); AM_AnimIt++) {
		if (AM_AnimIt->a_name == a) {
			string last_state = AM_state != "" ? AM_state : a;
			AM_state = a;
			if (AM_AnimIt->a_type == getAnimation(last_state).a_type) {
				AM_foto_gram = AM_foto_gram;
			}
			else {
				AM_foto_gram = 0;
				Time = 0;
			}
			AM_animated_object->setTextureRect(sf::IntRect(AM_texture_size.x * AM_AnimIt->a_coords[AM_foto_gram].x, AM_texture_size.y * AM_AnimIt->a_coords[AM_foto_gram].y, AM_texture_size.x, AM_texture_size.y));
			return;
		}
	}
	throw runtime_error("Estado no existente");
}

void Animator_Manager::SetVelocity(float v)
{
	AM_velocity = v;
}

void Animator_Manager::SetTexture(const string & AM_location, int x, int y)
{
	AM_texture.loadFromFile(AM_location);
	AM_animated_object->setTexture(&AM_texture);
	AM_texture_size = AM_texture.getSize();
	AM_texture_size.x /= x;
	AM_texture_size.y /= y;
}

string Animator_Manager::getState()
{
	return AM_state;
}

Animator_Manager::Animation& Animator_Manager::getAnimation(const string& name)
{
	for (AM_AnimIt = AM_Animations.begin(); AM_AnimIt != AM_Animations.end(); AM_AnimIt++) {
		if (AM_AnimIt->a_name == name) {
			return *AM_AnimIt;
		}
	}
	throw runtime_error("Estado no existente");
}

void Animator_Manager::Init(sf::RectangleShape& AM_a_o, float v, const string& AM_location, int x, int y)
{
	AM_animated_object = &AM_a_o;
	AM_velocity = v;
	SetTexture(AM_location, x, y);
}

void Animator_Manager::Update(sf::Time deltaTime)
{
	Time += deltaTime.asSeconds();
	if (Time > AM_velocity) {
		Animation current_anim = getAnimation(AM_state);
		AM_foto_gram = (AM_foto_gram + 1) % current_anim.a_coords.size();
		Time = 0;
		AM_animated_object->setTextureRect(sf::IntRect(AM_texture_size.x * current_anim.a_coords[AM_foto_gram].x, AM_texture_size.y * current_anim.a_coords[AM_foto_gram].y, AM_texture_size.x, AM_texture_size.y));
	}
}

void Animator_Manager::Render()
{
}

void Animator_Manager::Destroy()
{
	AM_animated_object = nullptr;
}
