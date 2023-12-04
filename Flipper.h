#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Flipper
{
private:
	sf::Keyboard::Key input;
	sf::Vector2f size = {120, 30};

public:
	float speed = 360.f;
	float maxAngle = 0.f;
	float baseAngle = -30.f;
	sf::RectangleShape flipperShape;
	bool isDroit;
	void Init(sf::Vector2f pos, sf::Keyboard::Key inputA, sf::Keyboard::Key inputB);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

