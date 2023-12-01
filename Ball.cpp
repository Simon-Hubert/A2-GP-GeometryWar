#include "Ball.h"

void Ball::InitBall()
{
	int radius = 25;
	ball.setFillColor(sf::Color::Green);
	ball.setPosition(550, 120);
	ball.setRadius(radius);
	ball.setOrigin(radius, radius);
	//speed.y = 1;
}

void Ball::MoveBall(float deltaTime)
{

	pos = ball.getPosition();
	//speed.y= speed.y+ (deltaTime * gravity);
	pos.y = pos.y + (speed.y * deltaTime);
	pos.x = pos.x + (speed.x * deltaTime);
	
	ball.setPosition(pos);
}

void Ball::DrawBall(sf::RenderWindow& window)
{
		window.draw(ball);
}

void Ball::UpdateBall(float deltaTime)
{
	speed.y = speed.y + (deltaTime * gravity * 10.f);
}

void Ball::BounceBall(Collision::CollisionInfo info, float mulV, float deltaTime)
{
		if (info.isColliding)
	{
		float magSpeed = sqrt(speed.x * speed.x + speed.y * speed.y);
		magSpeed += mulV;
		float angleB =  atan2(- info.normal.y, - info.normal.x) + atan2(speed.y, speed.x);
		float angle = atan2(info.normal.y, info.normal.x) + angleB;
		speed.x = -magSpeed* cos(angle);
		speed.y = magSpeed* sin(angle);
		speed += info.penetration * info.normal;

		//pos.x = pos.x + speed.x * deltaTime;
		//pos.y = pos.y + speed.y * deltaTime;
		//ball.setPosition(pos);
	}
	else
	{
		//pos.y = pos.y;
		//ball.setPosition(pos);
	}
}

