#include "Ball.h"

void Ball::InitBall()
{
	ball.setFillColor(sf::Color::Green);
	ball.setPosition(640, 360);
	ball.setRadius(50);
}

void Ball::MoveBall(float deltaTime)
{
	speed = speed + (deltaTime * gravity);
	pos = ball.getPosition();
	pos.y = pos.y + speed;
	ball.setPosition(pos);
}

void Ball::DrawBall(sf::RenderWindow& window)
{
		window.draw(ball);
}
