#include "Player.h"
#include "Game.h"


Player::Player(sf::Vector2f size)
{
	p_shape.setSize(size);
}


Player::~Player()
{
}

void Player::Init(sf::Vector2f pos)
{
	Object::Init(pos);
	p_AM.Init(p_shape, .2f, "CharactersAnimations/May be it is.png", 12, 8);
	p_AM.setAnimation({ sf::Vector2u{9, 0}, sf::Vector2u{10, 0}, sf::Vector2u{11, 0}, sf::Vector2u{10, 0} }, "abajo", Animator_Manager::movement);
	p_AM.setAnimation({ sf::Vector2u{9, 3}, sf::Vector2u{10, 3}, sf::Vector2u{11, 3}, sf::Vector2u{10, 3} }, "arriba", Animator_Manager::movement);
	p_AM.setAnimation({ sf::Vector2u{9, 2}, sf::Vector2u{10, 2}, sf::Vector2u{11, 2}, sf::Vector2u{10, 2} }, "derecha", Animator_Manager::movement);
	p_AM.setAnimation({ sf::Vector2u{9, 1}, sf::Vector2u{10, 1}, sf::Vector2u{11, 1}, sf::Vector2u{10, 1} }, "izquierda", Animator_Manager::movement);
	p_AM.setAnimation({ sf::Vector2u{10, 0} }, "idle_abajo", Animator_Manager::idle);
	p_AM.setAnimation({ sf::Vector2u{10, 3} }, "idle_arriba", Animator_Manager::idle);
	p_AM.setAnimation({ sf::Vector2u{10, 2} }, "idle_derecha", Animator_Manager::idle);
	p_AM.setAnimation({ sf::Vector2u{10, 1} }, "idle_izquierda", Animator_Manager::idle);
	p_AM.SetState("idle_abajo");
}

void Player::Update(sf::Time deltaTime)
{
	Object::Update(deltaTime);
	sf::Vector2f movement;
	if (mIsMovingUp) {
		p_Animation().SetState("arriba");
		movement.y -= 1;
	}
	if (mIsMovingDown) {
		p_Animation().SetState("abajo");
		movement.y += 1;
	}
	if (mIsMovingLeft) {
		p_Animation().SetState("izquierda");
		movement.x -= 1;
	}
	if (mIsMovingRight) {
		p_Animation().SetState("derecha");
		movement.x += 1;
	}
	move(movement * deltaTime.asSeconds());
}

void Player::handleInputs(sf::Keyboard::Key key, bool isPressed)
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

void Player::Render(sf::RenderWindow* game_window)
{
	Object::Render(game_window);
}

void Player::Destroy()
{
}

void Player::move(sf::Vector2f p_move)
{
	p_movement = p_move * Speed;
}
