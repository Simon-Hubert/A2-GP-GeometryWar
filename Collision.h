#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#pragma once
namespace Collision
{
	struct CollisionInfo
	{
		bool isColliding;
		sf::Vector2f normal;
		float penetration;
	};
	CollisionInfo CircleToCircle(sf::CircleShape circle1, sf::CircleShape circle2);
	CollisionInfo CircleToRectFrames(sf::CircleShape circle, sf::Vector2f pos, sf::RectangleShape rect);
	CollisionInfo CircleToRectangle(sf::CircleShape circle, sf::RectangleShape rectangle);
	CollisionInfo CircleToOrientedRectangle(sf::CircleShape circle, sf::RectangleShape rectangle);
}