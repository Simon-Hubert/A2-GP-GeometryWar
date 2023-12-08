#include "Player.h"
#define TAU 6.28318530718

void Player::Init(sf::Vector2f pos, int largeur, bool player1)
{
	position = pos;
	flipperDroit.isDroit = true;
	flipperGauche.isDroit = false;
	sf::Keyboard::Key inputA = sf::Keyboard::Key::Q;
	sf::Keyboard::Key inputB = sf::Keyboard::Key::D;
	flipperDroit.player1 = true;
	flipperGauche.player1 = true;
	if (!player1) {
		flipperDroit.player1 = false;
		flipperGauche.player1 = false;
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
	flipperDroit.Init(position, largeur, inputA, inputB);
	flipperGauche.Init(position, largeur, inputA, inputB);
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

Flipper* Player::getFlipper(bool Droit)
{
	return Droit ? &flipperDroit : &flipperGauche;
}
