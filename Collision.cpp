#include "Collision.h"

using namespace Collision;

CollisionInfo Collision::CircleToCircle(sf::CircleShape circle1, sf::CircleShape circle2)
{
	CollisionInfo info;
	int m = sqrt((circle1.getPosition().x - circle2.getPosition().x) * (circle1.getPosition().x - circle2.getPosition().x) + (circle1.getPosition().y - circle2.getPosition().y) * (circle1.getPosition().y - circle2.getPosition().y));
	if (m <= circle1.getRadius() + circle2.getRadius())
	{
		info.isColliding = true;
		info.normal= sf::Vector2f(circle1.getPosition().x - circle2.getPosition().x, circle1.getPosition().y - circle2.getPosition().y);
		info.normal = info.normal / sqrt(info.normal.x * info.normal.x + info.normal.y * info.normal.y); // permet au vecteur d'indiquer une direction et une intensité 1
		return info;
	}
	info.isColliding = false;
	info.normal = sf::Vector2f(0, 0);
	return info;
}

bool Collision::CircleToRectangle(sf::CircleShape circle, sf::RectangleShape& rectangle)
{
	return false;
}
