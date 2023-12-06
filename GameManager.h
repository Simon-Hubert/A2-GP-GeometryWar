#include "const.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.h"
#include <iostream>

#pragma once
class GameManager
{
private:
	sf::Font font;
	sf::Text J1, J2, winner;
	std::string j1String, j2String;

public:
	int scoreJ1 = 0, scoreJ2 = 0;
	void RepoBall(Ball& ballToReplace);
	void UpdateScore(bool isP1, Ball& ballToReplace);
	void InitUI();
	void UpdateUI();
	void DrawUI(sf::RenderWindow& window);
	void Winner(bool isJ1);
	void DrawWinner(sf::RenderWindow& window);
	
};

