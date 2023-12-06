#include "Ball.h"


void Ball::InitBall()
{
	int radius = 15;
	ball.setFillColor(sf::Color::Green);
	ball.setPosition(WINDOW_W/2, WINDOW_H/2);
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
		//speed.y = speed.y - (deltaTime * gravity * 10.f);
		float magSpeed = sqrt(speed.x * speed.x + speed.y * speed.y);
		float minSpeed = 150;
		float maxSpeed = 500;
		magSpeed = magSpeed * mulV > maxSpeed ? maxSpeed : magSpeed * mulV;
		if (magSpeed * mulV < minSpeed) magSpeed = minSpeed;
		else magSpeed *= mulV;
		float angleB =  atan2(-info.normal.y, -info.normal.x) - atan2(speed.y, speed.x);
		float angle = atan2(-info.normal.y,- info.normal.x) + angleB;
		if (angleB == 0) {
			speed = magSpeed * info.normal;
		}
		else if(angleB > 0)
		{
			speed.x = -magSpeed* cos(angle);
			speed.y = magSpeed* sin(angle);
		}
		else 
		{
			speed.x = -magSpeed * cos(angle);
			speed.y = magSpeed * -sin(angle);
		}
		//speed = info.normal * magSpeed;
		//sf::Vector2f dir = sf::Vector2f(-cos(angle), sin(angle));
		pos = pos + info.penetration * info.normal;
		ball.setPosition(pos);
		//std::cout << info.normal.x << " "<< info.normal.y << "\n";
	}
}

