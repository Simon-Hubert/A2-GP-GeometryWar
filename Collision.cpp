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
		info.penetration = circle1.getRadius() + circle2.getRadius() - m;
		//std::cout << info.penetration << "\n";
		return info;
	}

	info.isColliding = false;
	info.normal = sf::Vector2f(1, 0);
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

	float r = circle.getRadius();
	circle.setOrigin(r, r);

	sf::Vector2f rectOrigin = rectangle.getOrigin();
	//std::cout << rectOrigin.x << " " << rectOrigin.y << "\n";
	rectangle.setOrigin(0,0);
	rectangle.move(-rectOrigin);

	sf::Vector2f rectPos = rectangle.getPosition();
	sf::Vector2f circlePos = circle.getPosition();
	sf::Vector2f rectSize = rectangle.getSize();

	sf::Vector2f test = sf::Vector2f(circlePos.x, circlePos.y);

	if (circlePos.x < rectPos.x) test.x = rectPos.x;
	else if (circlePos.x > rectPos.x + rectSize.x) test.x = rectPos.x + rectSize.x;

	if (circlePos.y < rectPos.y) test.y = rectPos.y;
	else if (circlePos.y > rectPos.y + rectSize.y) test.y = rectPos.y + rectSize.y;

	sf::Vector2f dist = sf::Vector2f(circlePos.x - test.x , circlePos.y - test.y );
	float distance = sqrt(dist.x * dist.x + dist.y * dist.y);

	//std::cout << circlePos.x << " " << test.x << "\n";

	if (distance <= r) {
		if (distance != 0) {
			dist = dist / distance;
		}
		else dist = sf::Vector2f(1, 0);
		info.normal = dist;
		//std::cout << "Collision ! ! !\n";
		info.penetration = r - distance;
		std::cout << info.penetration << std::endl;
		info.isColliding = true;
	}
	return info;


	//CollisionInfo info;
	//info.isColliding = false;
	//info.normal = {};
	//info.penetration = 0;


	//sf::Vector2f sizeRect = rectangle.getSize();
	//sf::Vector2f pos = rectangle.getPosition();

	//rectangle.setOrigin(sizeRect / 2.f);

	//sf::Vector2f cR = circle.getPosition();
	//float r = circle.getRadius();

	////calcul point rectangle
	//sf::Vector2f tl = { pos.x - (sizeRect.x/2), pos.y - (sizeRect.y / 2) };
	//sf::Vector2f tr = { pos.x + (sizeRect.x/2), pos.y - (sizeRect.y / 2) };
	//sf::Vector2f br = { pos.x + (sizeRect.x/2), pos.y + (sizeRect.y / 2) };
	//sf::Vector2f bl = { pos.x - (sizeRect.x/2), pos.y + (sizeRect.y / 2) };

	////est ce que C est dans mon rectangle ?
	//if (cR.x  >= tl.x - r &&
	//	cR.x  <= br.x + r &&
	//	cR.y  >= tl.y - r &&
	//	cR.y  <= br.y + r)
	//{
	//	std::cout << "collision !!!!!!!!!\n";
	//	info.isColliding = true;
	//	bool a = cR.x >= tr.x - r;
	//	bool b = cR.y >= tr.y + r;
	//	bool c = cR.x <= bl.x + r;
	//	bool d = cR.y <= bl.y - r;
	//	info.normal = { 0,0 };
	//	info.normal.x = a ? 1 : 0;
	//	info.normal.x = c ? -1 : 0;
	//	info.normal.y = b ? 1 : 0;
	//	info.normal.y = d ? -1 : 0;
	//	// normaliser la normale
	//	//std::cout << info.normal.x <<" "<<info.normal.y << "\n";
	//	float penV = r + (sizeRect.x/ 2.f) - abs(cR.x - pos.x);
	//	float penH = r + (sizeRect.y/ 2.f) - abs(cR.y - pos.y);
	//	float penD = penV + penH;

	//	info.penetration = a || c ? penH : info.penetration;
	//	info.penetration = b || d ? penV : info.penetration;

	//	std::cout << info.penetration << "\n";
	//	info.penetration = 0;
	//}
	//return info;
}

CollisionInfo Collision::CircleToOrientedRectangle(sf::CircleShape circle, sf::RectangleShape rectangle)
{
	sf::Vector2f posRect = rectangle.getPosition();
	float rotation = rectangle.getRotation();
	//rotation = rotation >= 180 ? rotation - 360 : rotation;
	float deg2rad = 6.28318530718f / 360.f;
	rotation = rotation * deg2rad;

	//Changement de Base pour se ramener à une situation AABB
	//Translation
	rectangle.move(-posRect);
	circle.move(-posRect);

	//Rotation
	sf::Vector2f posCirc = circle.getPosition();
	//Matrice de rotation en 2 Dim :
	//std::cout << posCirc.x << " " << posCirc.y << "\n";
	float x = posCirc.x * cos(-rotation) - posCirc.y * sin(-rotation);
	float y = posCirc.x * sin(-rotation) + posCirc.y * cos(-rotation);
	circle.setPosition(x, y);
	//std::cout << x << " " << y << "\n";
	rectangle.rotate(-rotation/deg2rad);

	CollisionInfo info = CircleToRectangle(circle, rectangle);

	x = info.normal.x;
	y = info.normal.y;
	//std::cout << info.normal.x << " "<< info.normal.y << "\n";
	info.normal.x = x * cos(rotation) - y * sin(rotation);
	info.normal.y = x * sin(rotation) + y * cos(rotation);
	//std::cout << info.normal.x << " "<< info.normal.y << "\n";


	return info;
}
