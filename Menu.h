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
		sf::CircleShape ball;
		const int n = 10;
		sf::CircleShape traine[10];
		sf::Vector2f speedBall = { 500, 500 };
		sf::Vector2f posBall = {};
		bool select;
		int index = 0;
		bool startGame;
		float radius;
		void Selection();
		void Trail();

	public:
		void InitMenu();
		void MoveBallMenu(float deltaTime);
		bool Controller();
		void DrawMenu(sf::RenderWindow& window);
};

