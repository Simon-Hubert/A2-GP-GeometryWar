#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Collision.h"
#include <stdlib.h>
#include <thread>
#include <chrono>
using namespace Collision;
#pragma once
class Bounce
{

	sf::Vector2f pos;
	public:
	sf::CircleShape bouncer;
	float radiusMax;
	void InitBounce(sf::Color color, sf::Vector2f pos, float radius);
	CollisionInfo Bouncing(Collision::CollisionInfo info, float deltatime);
	void DrawBounce(sf::RenderWindow& window);
	void Animate(float deltatime);
	void UpdateAnm(float deltatime);
};

