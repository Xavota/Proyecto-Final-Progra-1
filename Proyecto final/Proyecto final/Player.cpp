#include "Player.h"
#include "Game.h"

Player::Player(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name)
{
	Init(pos, anims, name);
}

Player::~Player()
{
}

void Player::Init(sf::Vector2f pos, const vector<Animator_Manager::Animation>& anims, string name) // Inicializa al jugador como objeto
{
	Object::Init(pos, anims, name);
}

void Player::Update(sf::Time deltaTime) // Cada cilco
{
	Object::Update(deltaTime); // Lo updatea como objeto
	sf::Vector2f movement = { 0.f, 0.f };
	if (Speed != 0) { // Revisa que tenga velocidad el jugador. Depende a dónde se mueva le pone ese estado
		if (mIsMovingUp) {
			p_Animation().SetState(Animator_Manager::AnimationTypes::movement, Animator_Manager::AnimationFace::up);
			movement.y -= 1;
		}
		if (mIsMovingDown) {
			p_Animation().SetState(Animator_Manager::AnimationTypes::movement, Animator_Manager::AnimationFace::down);
			movement.y += 1;
		}
		if (mIsMovingLeft) {
			p_Animation().SetState(Animator_Manager::AnimationTypes::movement, Animator_Manager::AnimationFace::left);
			movement.x -= 1;
		}
		if (mIsMovingRight) {
			p_Animation().SetState(Animator_Manager::AnimationTypes::movement, Animator_Manager::AnimationFace::right);
			movement.x += 1;
		}
	}
	move(movement * deltaTime.asSeconds()); // Mueve al jugador
}

void Player::handleInputs(sf::Keyboard::Key key, bool isPressed) // Convierte los inputs en acciones
{
	if (key == sf::Keyboard::W) {
		mIsMovingUp = isPressed;
	}
	else if (key == sf::Keyboard::S) {
		mIsMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::A) {
		mIsMovingLeft = isPressed;
	}
	else if (key == sf::Keyboard::D) {
		mIsMovingRight = isPressed;
	}
}

void Player::Render(sf::RenderWindow* game_window) // Renderiza al jugador como Objeto
{
	Object::Render(game_window);
}

void Player::Destroy() // Libera la memoria
{
	Object::Destroy();
}

void Player::move(sf::Vector2f p_move) // Mueve al jugador
{
	p_movement = p_move * Speed;
}
