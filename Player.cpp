#include "Player.h"
#define TAU 6.28318530718

void Player::Init()
{
	flipperDroit.isDroit = true;
	flipperGauche.isDroit = false;
	flipperDroit.Init(position);
	flipperGauche.Init(position);
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
