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
		Item InitItem();
		void DrawItem(sf::RenderWindow& window);
		void CreatePowerUp();
		void CallPowerUp(bool* isItem);
		void DestroyItem(bool* isItem);
		Item FalseInitItem();
};