#include "Menu.h"
#include <iostream>

void Menu::InitMenu()
{
	radius = 25;
	ball.setFillColor(sf::Color::White);
	ball.setPosition(radius + 1, radius + 1);
	ball.setRadius(radius);
	ball.setOrigin(radius, radius);
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
	START.setPosition(WINDOW_W/2, (WINDOW_H/2) - WINDOW_H / 20);
	QUIT.setPosition(WINDOW_W/2, (WINDOW_H/2) + WINDOW_H/20);
	Controller();
}

void Menu::MoveBallMenu(float deltaTime)
{
	Trail();
	bool a = ball.getPosition().x + radius < WINDOW_W;
	bool b = ball.getPosition().x - radius > 0;
	bool c = ball.getPosition().y + radius < WINDOW_H;
	bool d = ball.getPosition().y - radius > 0;
	posBall = ball.getPosition();

	if (a && b && c && d)
	{
		speedBall = speedBall;
	}
	else if (a && b && (!c || !d))
	{
		speedBall.y = -speedBall.y;
	}
	else if ((!a || !b) && c && d)
	{
		speedBall.x = -speedBall.x;
	}
	posBall.x = posBall.x + (speedBall.x * deltaTime);
	posBall.y = posBall.y + (speedBall.y * deltaTime);
	ball.setPosition(posBall);
}

void Menu::Trail()
{
	traine[index].setPosition(posBall);
	traine[index].setRadius(radius);
	traine[index].setFillColor(sf::Color(255, 255, 255, 150));
	traine[index].setOrigin(radius, radius);
	index = (index + 1) % 10;

}

void Menu::DrawMenu(sf::RenderWindow& window)
{
	sf::RenderWindow& w = window;
	window.draw(START);
	window.draw(startText);
	window.draw(QUIT);
	for (int i = 0; i < n; i++)
	{
		window.draw(traine[i]);
	}
	window.draw(ball);
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
