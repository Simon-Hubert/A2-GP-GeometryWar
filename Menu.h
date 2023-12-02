#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#pragma once
class Menu
{
public:
	sf::Font font;
	bool select;
	bool startGame;
	sf::RectangleShape START;
	sf::Text startText;
	sf::RectangleShape QUIT;
	sf::Text quitText;
	void InitMenu();
	void Start(bool select);
	bool Controller();
	void Selection();
	void DrawMenu(sf::RenderWindow& window);
};

