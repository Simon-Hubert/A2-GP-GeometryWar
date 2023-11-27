#include "Player.h"

void Player::Init()
{
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(640, 360);
	rectangle.setSize(sf::Vector2f(128, 128));
}

void Player::UpdateLogic(float delta)
{
	sf::Vector2f pos = rectangle.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		pos.x = pos.x - delta * speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		pos.x = pos.x + delta * speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		pos.y = pos.y - delta * speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		pos.y = pos.y + delta * speed;

	rectangle.setPosition(pos);
}

void Player::Draw(sf::RenderWindow &window)
{
	window.draw(rectangle);
}
