#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player
{
private:
	sf::RectangleShape rectangle;
	float speed=500.f;

public:
	void Init();
	void UpdateLogic(float delta);
	void Draw(sf::RenderWindow &window);
};

