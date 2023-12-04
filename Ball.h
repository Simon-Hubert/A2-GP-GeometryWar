#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Collision.h"

using namespace Collision;

#pragma once

class Ball
{
	public:
		float gravity = 9.81f ;
		sf::CircleShape ball;
		sf::Vector2f pos;
		sf::Vector2f speed = {0, 0};
		void InitBall();
		void MoveBall(float deltaTime);
		void DrawBall(sf::RenderWindow& window);
		void UpdateBall(float deltaTime);
		void BounceBall(Collision::CollisionInfo info, float mulV, float deltaTime);
};

