#include "GameManager.h"

void GameManager::RepoBall(Ball& ballToReplace)
{
	ballToReplace.speed = { (float)(rand() % 20 + 10),0};
	ballToReplace.ball.setPosition(WINDOW_W / 2, WINDOW_H / 2);
}

void GameManager::UpdateScore(bool isP1, Ball& ballToReplace)
{
	if (isP1)
	{
		scoreJ1++;
		if (ballToReplace.gravity > 0)
		{
			ballToReplace.gravity *= -1;
		}
	}
	else {
		scoreJ2++;
		if (ballToReplace.gravity < 0)
		{
			ballToReplace.gravity *= -1;
		}
	}
}

void GameManager::InitUI()
{
	J1.setFont(font);
	J1.setString("J1: " + std::to_string(scoreJ1));
	J1.setCharacterSize(48);
	J1.setFillColor(sf::Color::White);
	J1.setStyle(sf::Text::Bold);
	J2.setFont(font);
	J2.setString("J2: " + std::to_string(scoreJ2));
	J2.setCharacterSize(48);
	J2.setFillColor(sf::Color::White);
	J2.setStyle(sf::Text::Bold);

	J1.setPosition(10, 10);
	J2.setPosition(10, 60);
	font.loadFromFile("../ARCADECLASSIC.ttf");
}

void GameManager::UpdateUI()
{
	J1.setString("J1: " + std::to_string(scoreJ1));
	J2.setString("J2: " + std::to_string(scoreJ2));
}

void GameManager::DrawUI(sf::RenderWindow& window)
{
	window.draw(J1);
	window.draw(J2);
}

void GameManager::Winner(bool isJ1)
{
	winner.setFont(font);
	winner.setCharacterSize(96);
	winner.setFillColor(sf::Color::Yellow);
	winner.setStyle(sf::Text::Bold);
	winner.setPosition(WINDOW_W / 2, WINDOW_H / 2);
	if (isJ1)
	{
		winner.setString("J1 WIN ! GG");
	}
	if (!isJ1)
	{
		winner.setString("J2 WIN ! GG");
	}
}

void GameManager::DrawWinner(sf::RenderWindow& window)
{
	window.draw(winner);
}
