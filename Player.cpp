#include "Player.h"
#define TAU 6.28318530718

void Player::Init(sf::Vector2f pos, bool player1)
{
	position = pos;
	flipperDroit.isDroit = true;
	flipperGauche.isDroit = false;
	sf::Keyboard::Key inputA = sf::Keyboard::Key::Q;
	sf::Keyboard::Key inputB = sf::Keyboard::Key::D;
	if (!player1) {
		float temp = -flipperDroit.maxAngle;
		flipperDroit.maxAngle = -flipperDroit.baseAngle;
		flipperGauche.maxAngle = -flipperDroit.baseAngle;
		flipperGauche.baseAngle = temp;
		flipperDroit.baseAngle = temp;
		flipperDroit.speed *= -1.0f;
		flipperGauche.speed *= -1.0f;
		inputA = sf::Keyboard::Key::J;
		inputB = sf::Keyboard::Key::L;
	}
	flipperDroit.Init(position, inputA, inputB);
	flipperGauche.Init(position, inputA, inputB);
}

void Player::Update(float deltaTime)
{
	flipperDroit.Update(deltaTime);
	flipperGauche.Update(deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	flipperDroit.Draw(window);
	flipperGauche.Draw(window);
}

Flipper Player::getFlipper(bool Droit)
{
	return Droit ? flipperDroit : flipperGauche;
}
