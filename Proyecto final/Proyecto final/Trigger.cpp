#include "Trigger.h"
#include "Game.h"

Game* Trigger::game = Game::getInstance();
Trigger::Trigger()
{
}

Trigger::~Trigger()
{
}

void Trigger::Init() // Inicializa el trigger
{
}

void Trigger::Update(sf::Time deltaTime) // Cada ciclo
{
}

void Trigger::Render(sf::RenderWindow * window) // Renderiza lo que necesite
{
	window->draw(t_zones);
}

void Trigger::Destory() // Libera memoria
{
	if (g_player != nullptr) {
		g_player = nullptr;
	}
	if (t_Interactuable != nullptr) {
		t_Interactuable = nullptr;
	}
	if (t_map != nullptr) {
		t_map = nullptr;
	}
	if (game != nullptr) {
		game = nullptr;
	}
}

void Trigger::handleInputs(sf::Keyboard::Key key, bool isPressed) // Convierte inputs en acciones
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

bool Trigger::TriggerIsMet() // Regresa si el trigger se cumplió
{
	switch (type) // Según el tipo de trigger, revisa si lo que necesita cumplirse se cumple
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
			if (g_player->p_shape.getGlobalBounds().intersects(sf::FloatRect(t_Interactuable->p_shape.getPosition().x,
				t_Interactuable->p_shape.getPosition().y - game->pixels / 4, t_Interactuable->p_shape.getSize().x, game->pixels / 4))
				&& g_player->p_AM.getAnimation().a_face == Animator_Manager::AnimationFace::down) 
			{
				t_Interactuable->SetState(Animator_Manager::AnimationFace::up);
				return true;
			}
			else if (g_player->p_shape.getGlobalBounds().intersects(sf::FloatRect(t_Interactuable->p_shape.getPosition().x,
				t_Interactuable->p_shape.getPosition().y + t_Interactuable->p_shape.getSize().y, t_Interactuable->p_shape.getSize().x, game->pixels / 4))
				&& g_player->p_AM.getAnimation().a_face == Animator_Manager::AnimationFace::up)
			{
				t_Interactuable->SetState(Animator_Manager::AnimationFace::down);
				return true;
			}
			else if (g_player->p_shape.getGlobalBounds().intersects(sf::FloatRect(t_Interactuable->p_shape.getPosition().x - game->pixels / 4,
				t_Interactuable->p_shape.getPosition().y, game->pixels / 4, t_Interactuable->p_shape.getSize().y))
				&& g_player->p_AM.getAnimation().a_face == Animator_Manager::AnimationFace::right)
			{
				t_Interactuable->SetState(Animator_Manager::AnimationFace::left);
				return true;
			}
			else if (g_player->p_shape.getGlobalBounds().intersects(sf::FloatRect(t_Interactuable->p_shape.getPosition().x + t_Interactuable->p_shape.getSize().x,
				t_Interactuable->p_shape.getPosition().y, game->pixels / 4, t_Interactuable->p_shape.getSize().y))
				&& g_player->p_AM.getAnimation().a_face == Animator_Manager::AnimationFace::left)
			{
				t_Interactuable->SetState(Animator_Manager::AnimationFace::right);
				return true;
			}
		}
		return false;
	case on_pos_interact:
		if (EnterPressed) {
			EnterPressed = false;
			return g_player->p_shape.getGlobalBounds().intersects(sf::FloatRect(t_pos_interractuable.x, t_pos_interractuable.y - game->pixels / 4,
				game->pixels, game->pixels / 4))
				&& g_player->p_AM.getAnimation().a_face == Animator_Manager::AnimationFace::down 
				|| g_player->p_shape.getGlobalBounds().intersects(sf::FloatRect(t_pos_interractuable.x, t_pos_interractuable.y + game->pixels,
				game->pixels, game->pixels / 4))
				&& g_player->p_AM.getAnimation().a_face == Animator_Manager::AnimationFace::up 
				|| g_player->p_shape.getGlobalBounds().intersects(sf::FloatRect(t_pos_interractuable.x - game->pixels / 4, t_pos_interractuable.y,
				game->pixels / 4, game->pixels))
				&& g_player->p_AM.getAnimation().a_face == Animator_Manager::AnimationFace::right 
				|| g_player->p_shape.getGlobalBounds().intersects(sf::FloatRect(t_pos_interractuable.x + game->pixels, t_pos_interractuable.y,
				game->pixels / 4, game->pixels))
				&& g_player->p_AM.getAnimation().a_face == Animator_Manager::AnimationFace::left;
		}
		return false;
	case on_map_enter:
		if (!onMap && t_map->inMap) {
			onMap = true;
			return true;
		}
		if (!t_map->inMap) {
			onMap = false;
		}
		return false;
	default:
		break;
	}
	return false;
}

Trigger Trigger::onTriggerEnter(sf::Vector2i init, sf::Vector2i fin) // Devuelve un trigger con la etiqueta "on triger enter"
{
	Trigger trig = Trigger();
	trig.type = triggers::on_trigger_enter;
	trig.t_zones = sf::RectangleShape(sf::Vector2f(max(fin.x, init.x) * game->pixels - min(fin.x, init.x) * game->pixels, max(fin.y, init.y) * game->pixels - min(fin.y, init.y) * game->pixels));
	trig.t_zones.setPosition(min(init.x, fin.x) * game->pixels, min(init.y, fin.y) * game->pixels);
	trig.t_zones.setFillColor(sf::Color::Color(0.f, 255.f, 0.f, 100.f));
	trig.g_player = trig.game->g_player;
	return trig;
}

Trigger Trigger::onTriggerExit(sf::Vector2i init, sf::Vector2i fin) // Devuelve un trigger con la etiqueta "on triger exit"
{
	Trigger trig = Trigger();
	trig.type = triggers::on_triger_exit;
	trig.t_zones = sf::RectangleShape(sf::Vector2f(max(fin.x, init.x) * game->pixels - min(fin.x, init.x) * game->pixels, max(fin.y, init.y) * game->pixels - min(fin.y, init.y) * game->pixels));
	trig.t_zones.setPosition(min(init.x, fin.x) * game->pixels, min(init.y, fin.y) * game->pixels);
	trig.t_zones.setFillColor(sf::Color::Color(0.f, 255.f, 0.f, 100.f));
	trig.g_player = trig.game->g_player;
	return trig;
}

Trigger Trigger::onTriggerStay(sf::Vector2i init, sf::Vector2i fin) // Devuelve un trigger con la etiqueta "on triger stay"
{
	Trigger trig = Trigger();
	trig.type = triggers::on_trigger_stay;
	trig.t_zones = sf::RectangleShape(sf::Vector2f(max(fin.x, init.x) * game->pixels - min(fin.x, init.x) * game->pixels, max(fin.y, init.y) * game->pixels - min(fin.y, init.y) * game->pixels));
	trig.t_zones.setPosition(min(init.x, fin.x) * game->pixels, min(init.y, fin.y) * game->pixels);
	trig.t_zones.setFillColor(sf::Color::Color(0.f, 255.f, 0.f, 100.f));
	trig.g_player = trig.game->g_player;
	return trig;
}

Trigger Trigger::onKeyPressed() // Devuelve un trigger con la etiqueta "on key pressed"
{
	return Trigger();
}

Trigger Trigger::onKeyReleased() // Devuelve un trigger con la etiqueta "on key released"
{
	return Trigger();
}

Trigger Trigger::onKey() // Devuelve un trigger con la etiqueta "on key"
{
	return Trigger();
}

Trigger Trigger::onInteract(Object * interactuable) // Devuelve un trigger con la etiqueta "on interact"
{
	Trigger trig = Trigger();
	trig.type = triggers::on_interact;
	trig.t_Interactuable = interactuable;
	trig.g_player = trig.game->g_player;
	return trig;
}

Trigger Trigger::onInteract(sf::Vector2i pos) // Devuelve un trigger con la etiqueta "on pos interact"
{
	Trigger trig = Trigger();
	trig.type = triggers::on_pos_interact;
	trig.t_pos_interractuable = { pos.x * game->pixels, pos.y * game->pixels };
	trig.g_player = trig.game->g_player;
	return trig;
}

Trigger Trigger::onMapEnter(Map * map) // Devuelve un trigger con la etiqueta "on map enter"
{
	Trigger trig = Trigger();
	trig.type = triggers::on_map_enter;
	trig.t_map = map;
	trig.g_player = trig.game->g_player;
	return trig;
}