#include "Trigger.h"



Trigger::Trigger()
{
}


Trigger::~Trigger()
{
}

void Trigger::Init()
{
}

void Trigger::Update(sf::Time deltaTime)
{
}

void Trigger::Render(sf::RenderWindow * window)
{
	window->draw(t_zones);
}

void Trigger::Destory()
{
}

void Trigger::handleInputs(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Return) {
		if (!key_pressed) {
			key_pressed = true;
			EnterPressed = isPressed;
		}
		else if (!isPressed) {
			key_pressed = isPressed;
		}
	}
}

bool Trigger::TriggerIsMet()
{
	switch (type)
	{
	case Trigger::on_trigger_enter:
		if (!inside) {
			inside = g_player->p_shape.getGlobalBounds().intersects(this->t_zones.getGlobalBounds());
			return g_player->p_shape.getGlobalBounds().intersects(this->t_zones.getGlobalBounds());
		}
		inside = g_player->p_shape.getGlobalBounds().intersects(this->t_zones.getGlobalBounds());
		return false;
	case Trigger::on_triger_exit:
		if (inside) {
			inside = g_player->p_shape.getGlobalBounds().intersects(this->t_zones.getGlobalBounds());
			return !g_player->p_shape.getGlobalBounds().intersects(this->t_zones.getGlobalBounds());
		}
		inside = g_player->p_shape.getGlobalBounds().intersects(this->t_zones.getGlobalBounds());
		return false;
	case Trigger::on_trigger_stay:
		return g_player->p_shape.getGlobalBounds().intersects(this->t_zones.getGlobalBounds());
		break;
	case Trigger::on_key_pressed:
		break;
	case Trigger::on_key_released:
		break;
	case Trigger::on_key:
		break;
	case Trigger::on_interact:
		if (EnterPressed) {
			EnterPressed = false;
			return g_player->p_shape.getGlobalBounds().intersects(sf::FloatRect(t_Interactuable->p_shape.getPosition().x, t_Interactuable->p_shape.getPosition().y - 20.f, t_Interactuable->p_shape.getSize().x, 20.f))
				|| g_player->p_shape.getGlobalBounds().intersects(sf::FloatRect(t_Interactuable->p_shape.getPosition().x, t_Interactuable->p_shape.getPosition().y + t_Interactuable->p_shape.getSize().y, t_Interactuable->p_shape.getSize().x, 20.f))
				|| g_player->p_shape.getGlobalBounds().intersects(sf::FloatRect(t_Interactuable->p_shape.getPosition().x - 20.f, t_Interactuable->p_shape.getPosition().y, 20.f, t_Interactuable->p_shape.getSize().y))
				|| g_player->p_shape.getGlobalBounds().intersects(sf::FloatRect(t_Interactuable->p_shape.getPosition().x + t_Interactuable->p_shape.getSize().x, t_Interactuable->p_shape.getPosition().y, 20.f, t_Interactuable->p_shape.getSize().y));
		}
		return false;
	default:
		break;
	}
}

Trigger* Trigger::onTriggerEnter(int x1, int y1, int x2, int y2, Player* player)
{
	Trigger* trig = new Trigger();
	trig->type = triggers::on_trigger_enter;
	trig->t_zones = sf::RectangleShape(sf::Vector2f(max(x2, x1) * 64.f - min(x2, x1) * 64.f, max(y2, y1) * 64.f - min(y2, y1) * 64.f));
	trig->t_zones.setPosition(min(x2, x1) * 64.f, min(y2, y1) * 64.f);
	trig->t_zones.setFillColor(sf::Color::Color(0.f, 255.f, 0.f, 100.f));
	trig->g_player = player;
	return trig;
}

Trigger* Trigger::onTriggerExit(int x1, int y1, int x2, int y2, Player* player)
{
	Trigger* trig = new Trigger();
	trig->type = triggers::on_triger_exit;
	trig->t_zones = sf::RectangleShape(sf::Vector2f(max(x2, x1) * 64.f - min(x2, x1) * 64.f, max(y2, y1) * 64.f - min(y2, y1) * 64.f));
	trig->t_zones.setPosition(min(x2, x1) * 64.f, min(y2, y1) * 64.f);
	trig->t_zones.setFillColor(sf::Color::Color(0.f, 255.f, 0.f, 100.f));
	trig->g_player = player;
	return trig;
}

Trigger* Trigger::onTriggerStay(int x1, int y1, int x2, int y2, Player* player)
{
	Trigger* trig = new Trigger();
	trig->type = triggers::on_trigger_stay;
	trig->t_zones = sf::RectangleShape(sf::Vector2f(max(x2, x1) - min(x2, x1), max(y2, y1) - min(y2, y1)));
	trig->t_zones.setPosition(min(x2, x1), min(y2, y1));
	trig->t_zones.setFillColor(sf::Color::Color(0.f, 255.f, 0.f, 100.f));
	trig->g_player = player;
	return trig;
}

Trigger* Trigger::onKeyPressed()
{
	return new Trigger();
}

Trigger* Trigger::onKeyReleased()
{
	return new Trigger();
}

Trigger* Trigger::onKey()
{
	return new Trigger();
}

Trigger * Trigger::onInteract(Object * interactuable, Player* player)
{
	Trigger* trig = new Trigger();
	trig->type = triggers::on_interact;
	trig->t_Interactuable = interactuable;
	trig->g_player = player;
	return trig;
}
