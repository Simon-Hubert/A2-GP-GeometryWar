#include "Bounce.h"


void Bounce::InitBounce(sf::Color color, sf::Vector2f pos)
{
	int radius = 50;
	bouncer.setFillColor(color);
	bouncer.setPosition(pos);
	bouncer.setRadius(radius);
	bouncer.setOrigin(radius, radius);

}

CollisionInfo Bounce::Bouncing(Collision::CollisionInfo info)
{
	return info;
}

void Bounce::DrawBounce(sf::RenderWindow& window)
{
	window.draw(bouncer);
}
