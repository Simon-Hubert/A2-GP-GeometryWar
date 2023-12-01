#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Flipper
{
private:
	float maxAngle = 30.f;
	float baseAngle;
	float speed = 180.f;

	sf::Keyboard::Key input;
	sf::Vector2f size = {120, 30};

public:
	sf::RectangleShape flipperShape;
	bool isDroit;
	void Init(sf::Vector2f pos);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

