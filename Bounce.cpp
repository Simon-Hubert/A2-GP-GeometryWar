#include "Bounce.h"


void Bounce::InitBounce(sf::Color color, sf::Vector2f pos, float radius)
{
	bouncer.setFillColor(color);
	bouncer.setPosition(pos);
	bouncer.setRadius(radius);
	bouncer.setOrigin(radius, radius);
	radiusMax = bouncer.getRadius() + 10;
}

CollisionInfo Bounce::Bouncing(Collision::CollisionInfo info, float deltatime)
{
	if (info.isColliding == true)
	{
		Animate(deltatime);
	}
	return info;
}

void Bounce::DrawBounce(sf::RenderWindow& window)
{
	window.draw(bouncer);
}
void Bounce::Animate(float deltaTime)
{
	sf::Color color = bouncer.getFillColor();
	sf::Clock timer;
	int randColor = rand() % 6;
	switch (randColor)
	{
	case 0:
		bouncer.setFillColor(sf::Color::Blue);
		break;

	case 1:
		bouncer.setFillColor(sf::Color::Yellow);
		break;
	case 2:
		bouncer.setFillColor(sf::Color::Red);
		break;
	case 3:
		bouncer.setFillColor(sf::Color::Cyan);
		break;
	case 4:
		bouncer.setFillColor(sf::Color::Green);
		break;
	case 5:
		bouncer.setFillColor(sf::Color::Magenta);
		break;
	case 6:
		bouncer.setFillColor(sf::Color::White);
		break;

	}	
}
