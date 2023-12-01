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

	sf::Vector2f position = { 640, 120 };

public:
	void Init();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

