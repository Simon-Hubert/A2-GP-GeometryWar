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
	if (info.isColliding == true)
	{
		Animate();
	}
	return info;
}

void Bounce::DrawBounce(sf::RenderWindow& window)
{
	window.draw(bouncer);
}
void Bounce::Animate()
{
	sf::Color color = bouncer.getFillColor();
	bouncer.setFillColor(sf::Color::Yellow);
	sf::Clock clock;
	float timeanm = clock.restart().asSeconds();
	if (timeanm > 1.f)
	{
		bouncer.setFillColor(color);
	}
}
