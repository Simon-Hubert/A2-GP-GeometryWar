#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#pragma once
class Menu
{
	private:
		sf::RectangleShape START;
		sf::Text startText;
		sf::RectangleShape QUIT;
		sf::Text quitText;
		sf::Font font;
		bool select;
		bool startGame;
		void Selection();

	public:
		void InitMenu();
		bool Controller();
		void DrawMenu(sf::RenderWindow& window);
};

