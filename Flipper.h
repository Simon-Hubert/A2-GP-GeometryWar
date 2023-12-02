#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Flipper
{
private:
	float maxAngle = 0.f;
	float baseAngle = -30.f;
	float speed = 360.f;

	sf::Keyboard::Key input;
	sf::Vector2f size = {120, 30};

public:
	sf::RectangleShape flipperShape;
	bool isDroit;
	void Init(sf::Vector2f pos);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

