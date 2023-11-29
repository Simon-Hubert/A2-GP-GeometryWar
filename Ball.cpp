#include "Ball.h"

void Ball::InitBall()
{
	int radius = 5;
	ball.setFillColor(sf::Color::Green);
	ball.setPosition(600, 200);
	ball.setRadius(radius);
	ball.setOrigin(radius, radius);
	speed.y = 1;
}

void Ball::MoveBall(float deltaTime, Collision::CollisionInfo cannotMove)
{

	pos = ball.getPosition();
	if (!cannotMove.isColliding)
	{
		speed.y = speed.y; //+ (deltaTime * gravity);
		pos.y = pos.y + speed.y;
		pos.x = pos.x + speed.x;
	}
	else {
		//speed = 0;
		pos.y = pos.y;

	}
	
	ball.setPosition(pos);
}

void Ball::DrawBall(sf::RenderWindow& window)
{
		window.draw(ball);
}

void Ball::BounceBall(Collision::CollisionInfo info, float mulV)
{
		if (info.isColliding)
	{
		float magSpeed = sqrt(speed.x * speed.x + speed.y * speed.y);
		magSpeed += mulV;
		float angleB =  atan2(- info.normal.y, - info.normal.x) + atan2(speed.y, speed.x);
		float angle = atan2(info.normal.y, info.normal.x) + angleB;
		speed.x = -magSpeed* cos(angle);
		speed.y = magSpeed* sin(angle);
		pos.x = pos.x + speed.x;
		pos.y = pos.y + speed.y;
		ball.setPosition(pos);
	}
	else
	{
		pos.y = pos.y;
		ball.setPosition(pos);
	}
}

