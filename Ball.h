#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#pragma once
class Ball
{
	float gravity = 9.81f;
	sf::CircleShape ball;
	sf::Vector2f pos;
	public:
		float speed = 1.0f;
		void InitBall();
		void MoveBall(float deltaTime);
		void DrawBall(sf::RenderWindow& window);
};

