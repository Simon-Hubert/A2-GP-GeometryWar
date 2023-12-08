#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<list>
#include "Ball.h"
#include "Bounce.h"
#include "Obstacle.h"
#include "Collision.h"
#include "Menu.h"
#include "Player.h"
#include "const.h"
#include "GameManager.h"
#include "PowerUp.h"
#include "Flipper.h"

using namespace Collision;
constexpr float cubeSpeed = 500.f;
int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Geometry Wars");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	// Début de la boucle de jeu
	GameManager manager;
	srand(time(NULL));
	manager.InitUI();
	bool j1Won = false, j2Won = false;
	bool isStarting = false;
	bool downGravity = true;
	Menu menu;
	sf::Clock frameClock;
	Item item;
	bool isItemActive = false;
	Ball ball;
	Player player11, player12, player21, player22;
	Bounce bounce1, bounce2, bounce3, bounce4, bounce5, bounce6, bounce7, bounce8 ;
	Obstacle wall1, wall2, wall3, wall4, wall5, wall6, wallSafe1, wallSafe2, wallSafe3, wallSafe4, wallBorder1, wallBorder2;

	player11.Init(sf::Vector2f(WINDOW_W * 0.5f, WINDOW_H * 0.89f), WINDOW_W / 5.5, true);
	player12.Init(sf::Vector2f(WINDOW_W * 0.5f, WINDOW_H * 0.6f), WINDOW_W / 2, true);
	player21.Init(sf::Vector2f(WINDOW_W * 0.5f, WINDOW_H * 0.11f), WINDOW_W / 5.5, false);
	player22.Init(sf::Vector2f(WINDOW_W * 0.5f, WINDOW_H * 0.4f), WINDOW_W / 2, false);

	bounce1.InitBounce(sf::Color::Red, sf::Vector2f(WINDOW_W * 0.4f, WINDOW_H * 0.7f), 20);
	bounce2.InitBounce(sf::Color::Red, sf::Vector2f(WINDOW_W * 0.6f, WINDOW_H * 0.3f), 20);
	bounce3.InitBounce(sf::Color::Blue, sf::Vector2f(WINDOW_W * 0.3f, WINDOW_H * 0.4f), 20);
	bounce4.InitBounce(sf::Color::Blue, sf::Vector2f(WINDOW_W * 0.7f, WINDOW_H * 0.6f), 20);


	wall1.InitWall(sf::Color::Red, sf::Vector2f(WINDOW_W * 0.f, WINDOW_H * 0.5f), sf::Vector2f(WINDOW_W * 0.2f, WINDOW_H * 0.01f));
	wall2.InitWall(sf::Color::Blue, sf::Vector2f(WINDOW_W, WINDOW_H * 0.5f), sf::Vector2f(WINDOW_W * 0.2f, WINDOW_H * 0.01f));
	wall3.InitWall(sf::Color::Red, sf::Vector2f(WINDOW_W * 0.9f, WINDOW_H * 0.79f - ((WINDOW_H * 0.15f) / 2)), sf::Vector2f(WINDOW_W * 0.015f, WINDOW_H * 0.15f));
	wall4.InitWall(sf::Color::Red, sf::Vector2f(WINDOW_W * 0.1f, WINDOW_H * 0.79f - ((WINDOW_H * 0.15f) / 2)), sf::Vector2f(WINDOW_W * 0.015f, WINDOW_H * 0.15f));
	wall5.InitWall(sf::Color::Blue, sf::Vector2f(WINDOW_W * 0.9f, WINDOW_H * 0.21f + ((WINDOW_H * 0.15f) / 2)), sf::Vector2f(WINDOW_W * 0.015f, WINDOW_H * 0.15f));
	wall6.InitWall(sf::Color::Blue, sf::Vector2f(WINDOW_W * 0.1f, WINDOW_H * 0.21f + ((WINDOW_H * 0.15f) / 2)), sf::Vector2f(WINDOW_W * 0.015f, WINDOW_H * 0.15f));
	wallSafe1.InitWall(sf::Color::White, sf::Vector2f(WINDOW_W * 0.85f, WINDOW_H * 0.81f), sf::Vector2f(WINDOW_W * 0.40f, WINDOW_H * 0.005f));
	wallSafe2.InitWall(sf::Color::White, sf::Vector2f(WINDOW_W * 0.15f, WINDOW_H * 0.81f), sf::Vector2f(WINDOW_W * 0.40f, WINDOW_H * 0.005f));
	wallSafe3.InitWall(sf::Color::White, sf::Vector2f(WINDOW_W * 0.15f, WINDOW_H * 0.19f), sf::Vector2f(WINDOW_W * 0.40f, WINDOW_H * 0.005f));
	wallSafe4.InitWall(sf::Color::White, sf::Vector2f(WINDOW_W * 0.85f, WINDOW_H * 0.19f), sf::Vector2f(WINDOW_W * 0.40f, WINDOW_H * 0.005f));
	wallBorder1.InitWall(sf::Color::Magenta, sf::Vector2f(0 - 5, WINDOW_H * 0.5f), sf::Vector2f(-10, WINDOW_H));
	wallBorder2.InitWall(sf::Color::Magenta, sf::Vector2f(WINDOW_W + 5, WINDOW_H * 0.5f), sf::Vector2f(10, WINDOW_H));

	ball.InitBall();

	wallSafe1.wall.rotate(-30.f);
	wallSafe3.wall.rotate(-30.f);
	wallSafe4.wall.rotate(30.f);
	wallSafe2.wall.rotate(30.f);

	std::list<Flipper*> flippers;
	flippers.push_front(player11.getFlipper(true));
	flippers.push_front(player11.getFlipper(false));
	flippers.push_front(player12.getFlipper(true));
	flippers.push_front(player12.getFlipper(false));
	flippers.push_front(player21.getFlipper(true));
	flippers.push_front(player21.getFlipper(false));
	flippers.push_front(player22.getFlipper(true));
	flippers.push_front(player22.getFlipper(false));

	std::list<Ball*> balls;
	balls.push_front(&ball);

	std::list<Bounce*> bounces;
	bounces.push_front(&bounce1);
	bounces.push_front(&bounce2);
	bounces.push_front(&bounce3);
	bounces.push_front(&bounce4);

	std::list<Obstacle*> obstacles;
	obstacles.push_front(&wall1);
	obstacles.push_front(&wall2);
	//obstacles.push_front(&wall3);
	//obstacles.push_front(&wall4);
	//obstacles.push_front(&wall5);
	//obstacles.push_front(&wall6);
	obstacles.push_front(&wallSafe1);
	obstacles.push_front(&wallSafe2);
	obstacles.push_front(&wallSafe3);
	obstacles.push_front(&wallSafe4);
	obstacles.push_front(&wallBorder1);
	obstacles.push_front(&wallBorder2);

	//std::list<Player> listPlayer;
	//listPlayer.push_front(player);

	menu.InitMenu();

	while (window.isOpen())
	{
		// Gérer les événéments survenus depuis le dernier tour de boucle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// On gère l'événément
			switch (event.type)
			{
			case sf::Event::Closed:
				// L'utilisateur a cliqué sur la croix => on ferme la fenêtre
				window.close();
				break;
			default:
				break;
			}
		}

		float deltaTime = frameClock.restart().asSeconds();

		// Logique
		if (isStarting == true)
		{
			player11.Update(deltaTime);
			player12.Update(deltaTime);
			player21.Update(deltaTime);
			player22.Update(deltaTime);
			std::list<Ball*>::iterator itB = balls.begin();
			std::list<Bounce*>::iterator itBo = bounces.begin();
			std::list<Obstacle*>::iterator itO = obstacles.begin();
			std::list<Flipper*>::iterator itF = flippers.begin();
			//std::cout << Collision::CircleToCircle(ball.ball, bounce.bouncer).normal.x << Collision::CircleToCircle(ball.ball, bounce.bouncer).normal.y << std::endl;
			item.CallPowerUp(isItemActive, deltaTime);
			item.DestroyItem(isItemActive, deltaTime, Collision::CircleToCircle(ball.ball, item.item).isColliding, ball);

			while (itB != balls.end())
			{
				(*(*itB)).UpdateBall(deltaTime);
				while (itBo != bounces.end())
				{
					(*(*itB)).BounceBall((*(*itBo)).Bouncing(Collision::CircleToCircle((*(*itB)).ball, (*(*itBo)).bouncer), deltaTime), .5f, deltaTime);
					itBo++;
				}
				while (itO != obstacles.end())
				{
					(*(*itB)).BounceBall(Collision::CircleToOrientedRectangle((*(*itB)).ball, (*(*itO)).wall), .5f, deltaTime);
					itO++;
				}
				while (itF != flippers.end()) {
					Collision::CollisionInfo col = Collision::CircleToOrientedRectangle((*(*itB)).ball, (*(*itF)).flipperShape);
					if (col.isColliding) {
						if (downGravity && (*(*itF)).player1) {
							downGravity = !downGravity;
							(*(*itB)).gravity *= -1;
							std::cout << "gravity changed1" << "\n";
						}
						else if (!downGravity && !(*(*itF)).player1){
							downGravity = !downGravity;
							(*(*itB)).gravity *= -1;
							std::cout << "gravity changed2" << "\n";
						}
						if (!ball.wasHit)
						{
							float mul = (*(*itF)).getLinearSpeed((*(*itB)).ball.getPosition()) / 20.f;
							std::cout << mul << std::endl;
							(*(*itB)).BounceBall(col, mul, deltaTime);
						}
						else 
						{
							(*(*itB)).BounceBall(col, 1, deltaTime);
						}
						ball.wasHit = true;
					}
					
					itF++;
				}
				ball.wasHit = false;
				(*(*itB)).MoveBall(deltaTime);
				itB++;
			}
			if (ball.ball.getPosition().y > WINDOW_H - ball.ball.getRadius())
			{
				manager.UpdateScore(false, ball);
				if (manager.scoreJ2 > 9)
				{
					j2Won = true;
					manager.Winner(false);
					isStarting = false;
				}
				manager.RepoBall(ball);
				downGravity = true;
			}
			if (ball.ball.getPosition().y < 0 + ball.ball.getRadius())
			{
				manager.UpdateScore(true, ball);
				manager.RepoBall(ball);
				if (manager.scoreJ1 > 9)
				{
					j1Won = true;
					manager.Winner(true);
					isStarting = false;
				}
				downGravity = false;
			}
		}
		else if (j1Won || j2Won)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				manager.scoreJ1 = 0;
				manager.scoreJ2 = 0;
				j1Won = false;
				j2Won = false;
				isStarting = false;
			}
		}
		else 
		{
			isStarting = menu.Controller();
			menu.MoveBallMenu(deltaTime);
		}

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		if (isStarting == true)
		{
			std::list<Ball*>::iterator itB = balls.begin();
			std::list<Bounce*>::iterator itBo = bounces.begin();
			std::list<Obstacle*>::iterator itO = obstacles.begin();
			std::list<Flipper*>::iterator itF = flippers.begin();
			while (itB != balls.end())
			{
				(*(*itB)).DrawBall(window);
				itB++;
			}
			while (itBo != bounces.end())
			{
				(*(*itBo)).DrawBounce(window);
				itBo++;
			}
			while (itO != obstacles.end())
			{
				(*(*itO)).DrawWall(window);
				itO++;
			}
			while (itF != flippers.end())
			{
				(*(*itF)).Draw(window);
				itF++;
			}
			item.DrawItem(window);
			manager.UpdateUI();
			manager.DrawUI(window);
		}
		else if (j1Won || j2Won)
		{
			manager.DrawWinner(window);
		}

		else 
		{
			menu.DrawMenu(window);
		}

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
