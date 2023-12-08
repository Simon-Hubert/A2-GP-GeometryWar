#include "Ball.h"

float dot(sf::Vector2f, sf::Vector2f);
sf::Vector2f normalized(sf::Vector2f);

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
	ball.move(speed * deltaTime);
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
		if (!isnan(info.normal.x))
		{
			//speed.y = speed.y - (deltaTime * gravity * 10.f);
			float magSpeed = sqrt(speed.x * speed.x + speed.y * speed.y);
			float minSpeed = 150;
			float maxSpeed = 500;
			//magSpeed = magSpeed * mulV > maxSpeed ? maxSpeed : magSpeed * mulV;
			//if (magSpeed * mulV < minSpeed) magSpeed = minSpeed;
			//else magSpeed *= mulV;
			if (magSpeed * mulV > maxSpeed || magSpeed * mulV < minSpeed)
			{
				magSpeed = magSpeed * mulV > maxSpeed ? maxSpeed : minSpeed;
			}
			else
			{
				magSpeed = magSpeed * mulV;
			}
			//std::cout << magSpeed << std::endl;
			sf::Vector2f u, w;
			u = dot(speed, info.normal) * info.normal;
			w = speed - u;
			speed = magSpeed * normalized(w - u);
			sf::Vector2f pos = ball.getPosition();
			//std::cout << pos.x << " " << pos.y << std::endl;
			pos = pos + info.penetration * info.normal;
			//std::cout << pos.x << " " << pos.y << std::endl;
			ball.setPosition(pos);
		}
		else {
			//std::cout << pos.x << " " << pos.y << std::endl;
		}
		//float angleB =  atan2(-info.normal.y, -info.normal.x) - atan2(speed.y, speed.x);
		//float angle = atan2(-info.normal.y,- info.normal.x) + angleB;
		//if (angleB == 0) {
		//	speed = magSpeed * info.normal;
		//}
		//else if(angleB > 0)
		//{
		//	speed.x = -magSpeed* cos(angle);
		//	speed.y = magSpeed* sin(angle);
		//}
		//else 
		//{
		//	speed.x = -magSpeed * cos(angle);
		//	speed.y = magSpeed * -sin(angle);
		//}
		//speed = info.normal * magSpeed;
		//sf::Vector2f dir = sf::Vector2f(-cos(angle), sin(angle));

		//std::cout << info.normal.x << " "<< info.normal.y << "\n";
	}
}

float dot(sf::Vector2f a, sf::Vector2f b) {
	return a.x * b.x + a.y * b.y;
}

sf::Vector2f normalized(sf::Vector2f v) {
	float a = sqrt(v.x * v.x + v.y + v.y);
	return v / a;
}
