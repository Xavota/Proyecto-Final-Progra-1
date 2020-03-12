#include "Trigger.h"
#include "Game.h"

Trigger::Trigger()
{
}


Trigger::~Trigger()
{
}
Game* Trigger::game = Game::getInstance();
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

Trigger* Trigger::onTriggerEnter(sf::Vector2f init, sf::Vector2f fin, Player* player)
{
	Trigger* trig = new Trigger();
	trig->type = triggers::on_trigger_enter;
	trig->t_zones = sf::RectangleShape(sf::Vector2f(max(fin.x, init.x) * game->pixels - min(fin.x, init.x) * game->pixels, max(fin.y, init.y) * game->pixels - min(fin.y, init.y) * game->pixels));
	trig->t_zones.setPosition(min(init.x, fin.x) * game->pixels, min(init.y, fin.y) * game->pixels);
	trig->t_zones.setFillColor(sf::Color::Color(0.f, 255.f, 0.f, 100.f));
	trig->g_player = player;
	return trig;
}

Trigger* Trigger::onTriggerExit(sf::Vector2f init, sf::Vector2f fin, Player* player)
{
	Trigger* trig = new Trigger();
	trig->type = triggers::on_triger_exit;
	trig->t_zones = sf::RectangleShape(sf::Vector2f(max(fin.x, init.x) * game->pixels - min(fin.x, init.x) * game->pixels, max(fin.y, init.y) * game->pixels - min(fin.y, init.y) * game->pixels));
	trig->t_zones.setPosition(min(init.x, fin.x) * game->pixels, min(init.y, fin.y) * game->pixels);
	trig->t_zones.setFillColor(sf::Color::Color(0.f, 255.f, 0.f, 100.f));
	trig->g_player = player;
	return trig;
}

Trigger* Trigger::onTriggerStay(sf::Vector2f init, sf::Vector2f fin, Player* player)
{
	Trigger* trig = new Trigger();
	trig->type = triggers::on_trigger_stay;
	trig->t_zones = sf::RectangleShape(sf::Vector2f(max(fin.x, init.x) * game->pixels - min(fin.x, init.x) * game->pixels, max(fin.y, init.y) * game->pixels - min(fin.y, init.y) * game->pixels));
	trig->t_zones.setPosition(min(init.x, fin.x) * game->pixels, min(init.y, fin.y) * game->pixels);
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
