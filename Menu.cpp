#include "Menu.h"

void Menu::InitMenu()
{
	font.loadFromFile("ARCADECLASSIC.ttf");
	select = false;
	START.setSize(sf::Vector2f(200, 50));
	START.setOrigin(START.getSize().x / 2, START.getSize().y / 2);
	START.setOutlineThickness(5);
	startText.setFont(font);
	startText.setString("START");
	startText.setCharacterSize(48);
	startText.setFillColor(sf::Color::Green);
	startText.setStyle(sf::Text::Bold);
	startText.setPosition(400, 100);
	START.setOutlineColor(sf::Color::White);
	QUIT.setSize(sf::Vector2f(200, 50));
	QUIT.setOrigin(START.getSize().x / 2, START.getSize().y / 2);
	QUIT.setOutlineThickness(5);
	QUIT.setOutlineColor(sf::Color::White);
	START.setPosition(1280/2, 300);
	QUIT.setPosition(1280/2, 400);
	Controller();
}

void Menu::DrawMenu(sf::RenderWindow& window)
{
	sf::RenderWindow& w = window;
	window.draw(START);
	window.draw(startText);
	window.draw(QUIT);
}

bool Menu::Controller()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (select)
		{
			select = !select;
		}
		Selection();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (!select)
		{
			select = !select;
		}
		Selection();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		return !select;
	}
	return false;
}

void Menu::Selection()
{
	if (select == false)
	{
		QUIT.setFillColor(sf::Color::Black);
		QUIT.setOutlineThickness(5);
		QUIT.setOutlineColor(sf::Color::White);
		START.setFillColor(sf::Color::White);
	}
	else 
	{
		START.setFillColor(sf::Color::Black);
		START.setOutlineThickness(5);
		START.setOutlineColor(sf::Color::White);
		QUIT.setFillColor(sf::Color::White);
	}
}
