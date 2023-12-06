#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Collision.h"
using namespace Collision;
#pragma once
class Bounce
{

	sf::Vector2f pos;
	public:
	sf::CircleShape bouncer;
	void InitBounce(sf::Color color, sf::Vector2f pos, float radius);
	CollisionInfo Bouncing(Collision::CollisionInfo info);
	void DrawBounce(sf::RenderWindow& window);
	void Animate();
};

