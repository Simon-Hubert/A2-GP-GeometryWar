#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Ball.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#pragma once

class Item {
	public : 
		sf::CircleShape item;
		sf::Vector2f pos;
		float chrono = 0;
		float chronokill = 0;
		Item InitItem();
		void DrawItem(sf::RenderWindow& window);
		void CallPowerUp(bool &isItem, float deltaTime);
		void DestroyItem(bool &isItem, float deltaTime, bool collision, Ball &ball);
		Item FalseInitItem();
		void CollisionItem(Ball &ball);
		void Powerup1(Ball &ball);
		void Powerup2();
		void TimeLife();
		void Cooldown();
};