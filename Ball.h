#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Collision.h"

using namespace Collision;

#pragma once

class Ball
{
	float gravity = 9.81f;
	public:
		sf::CircleShape ball;
		sf::Vector2f pos;
		sf::Vector2f speed = {0, 0};
		void InitBall();
		void MoveBall(float deltaTime, Collision::CollisionInfo canMove);
		void DrawBall(sf::RenderWindow& window);
		void UpdateBall();
		void BounceBall(Collision::CollisionInfo info, float mulV);
};

