#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "flipper.h"

class Player
{
private:
	Flipper flipperGauche;
	Flipper flipperDroit;
	bool flipGauche;
	bool flipDroit;

	sf::Vector2f position;

public:
	void Init(sf::Vector2f pos, bool player1);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	Flipper* getFlipper(bool Droit);
};

