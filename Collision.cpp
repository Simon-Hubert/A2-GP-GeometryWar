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
		info.normal = info.normal / sqrt(info.normal.x * info.normal.x + info.normal.y * info.normal.y); // permet au vecteur d'indiquer une direction et une intensit� 1
		info.penetration = circle1.getRadius() + circle2.getRadius() - m;
		//std::cout << info.penetration << "\n";
		return info;
	}

	info.isColliding = false;
	info.normal = sf::Vector2f(0, 0);
	info.penetration = 0;
	return info;
}

CollisionInfo Collision::CircleToRectFrames(sf::CircleShape circle, sf::Vector2f pos, sf::RectangleShape rect)
{
	sf::CircleShape ballClone = circle;
	ballClone.setPosition(pos);
	return CircleToRectangle(ballClone, rect);
}



CollisionInfo Collision::CircleToRectangle(sf::CircleShape circle, sf::RectangleShape rectangle)
{
	CollisionInfo info;
	info.isColliding = false;
	info.normal = {};
	info.penetration = 0;
	sf::Vector2f sizeRect = rectangle.getSize();
	sf::Vector2f pos = rectangle.getPosition();

	sf::Vector2f cR = circle.getPosition();
	float r = circle.getRadius();

	//calcul point rectangle
	sf::Vector2f tl = { pos.x - (sizeRect.x/2), pos.y - (sizeRect.y / 2) };
	sf::Vector2f tr = { pos.x + (sizeRect.x/2), pos.y - (sizeRect.y / 2) };
	sf::Vector2f br = { pos.x + (sizeRect.x/2), pos.y + (sizeRect.y / 2) };
	sf::Vector2f bl = { pos.x - (sizeRect.x/2), pos.y + (sizeRect.y / 2) };

	//est ce que C est dans mon rectangle ?
	if (cR.x  >= tl.x - r &&
		cR.x  <= br.x + r &&
		cR.y  >= tl.y - r &&
		cR.y  <= br.y + r)
	{
		std::cout << "collision !!!!!!!!!\n";
		info.isColliding = true;
		bool a = cR.x >= tr.x;
		bool b = cR.y >= tr.y;
		bool c = cR.x <= bl.x;
		bool d = cR.y <= bl.y;
		info.normal = { 0,0 };
		info.normal.x = a ? 1 : 0;
		info.normal.x = c ? -1 : 0;
		info.normal.y = b ? 1 : 0;
		info.normal.y = d ? -1 : 0;
		// normaliser la normale
		//std::cout << info.normal.x <<" "<<info.normal.y << "\n";
		float penV = r + (sizeRect.x/ 2.f) - abs(cR.x - pos.x);
		float penH = r + (sizeRect.y/ 2.f) - abs(cR.y - pos.y);
		float penD = penV + penH;

		info.penetration = a || c ? penH : info.penetration;
		info.penetration = b || d ? penV : info.penetration;
		if ((a || c) && (b || d)) {
			info.penetration = penD/2.f; // moyenne des 2 p�n�trations
			info.normal = info.normal * 0.7071f;
		}
		//std::cout << info.penetration << "\n";
		info.penetration = 30;
	}
	return info;
}

CollisionInfo Collision::CircleToOrientedRectangle(sf::CircleShape circle, sf::RectangleShape rectangle)
{
	sf::Vector2f posRect = rectangle.getPosition();
	float rotation = rectangle.getRotation();

	//Changement de Base pour se ramener � une situation AABB

	//Translation
	rectangle.move(-posRect);
	circle.move(-posRect);

	//Rotation
	sf::Vector2f posCirc = circle.getPosition();
	//Matrice de rotation en 2 Dim :
	float x = posCirc.x * cos(-rotation) + posCirc.y * sin(-rotation);
	float y = posCirc.y * cos(-rotation) - posCirc.x * sin(-rotation);
	circle.setPosition(x, y);
	rectangle.rotate(-rotation);

	CollisionInfo info = CircleToRectangle(circle, rectangle);
	//Changement inverse de Base

	//Rotation
	
	rectangle.rotate(rotation);
	posCirc.x = x * cos(rotation) + y * sin(rotation);
	posCirc.y = y * cos(rotation) - x * sin(rotation);
	x = info.normal.x;
	y = info.normal.y;
	info.normal.x = posCirc.x = x * cos(rotation) + y * sin(rotation);
	info.normal.y = posCirc.y = y * cos(rotation) - x * sin(rotation);
	circle.setPosition(posCirc);

	//Traslation
	rectangle.move(posRect);
	circle.move(posRect);

	return info;

}
