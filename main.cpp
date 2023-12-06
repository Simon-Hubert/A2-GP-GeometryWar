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

using namespace Collision;
constexpr float cubeSpeed = 500.f;
int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Geometry Wars");
	window.setVerticalSyncEnabled(true);

	// Début de la boucle de jeu
	GameManager manager;
	manager.InitUI();
	bool isStarting = false;
	bool downGravity = true;
	bool j1Won = false, j2Won = false;
	Menu menu;
	sf::Clock frameClock;
	Ball ball;
	Player player1, player2;
	Bounce bounce, bounce2;
	Obstacle wall;

	player1.Init(sf::Vector2f(340, WINDOW_H - 120), true);
	player2.Init(sf::Vector2f(340, 120), false);
	ball.InitBall();
	bounce.InitBounce(sf::Color::Red, sf::Vector2f(-600, 400));
	bounce.InitBounce(sf::Color::Magenta, sf::Vector2f(200, 600));
	bounce2.InitBounce(sf::Color::Blue, sf::Vector2f(1000, 460));
	wall.InitWall(sf::Color::White, sf::Vector2f(300, 400), sf::Vector2f(50, 100));

	std::list<Flipper*> flippers;
	flippers.push_front(player1.getFlipper(true));
	flippers.push_front(player1.getFlipper(false));
	flippers.push_front(player2.getFlipper(true));
	flippers.push_front(player2.getFlipper(false));

	std::list<Ball*> balls;
	balls.push_front(&ball);

	std::list<Bounce*> bounces;
	bounces.push_front(&bounce);
	bounces.push_front(&bounce2);

	std::list<Obstacle*> obstacles;
	obstacles.push_front(&wall);

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
			player1.Update(deltaTime);
			player2.Update(deltaTime);
			std::list<Ball*>::iterator itB = balls.begin();
			std::list<Bounce*>::iterator itBo = bounces.begin();
			std::list<Obstacle*>::iterator itO = obstacles.begin();
			std::list<Flipper*>::iterator itF = flippers.begin();
			//std::cout << Collision::CircleToCircle(ball.ball, bounce.bouncer).normal.x << Collision::CircleToCircle(ball.ball, bounce.bouncer).normal.y << std::endl;

			while (itB != balls.end())
			{
				(*(*itB)).UpdateBall(deltaTime);
				while (itBo != bounces.end())
				{
					(*(*itB)).BounceBall((*(*itBo)).Bouncing(Collision::CircleToCircle((*(*itB)).ball, (*(*itBo)).bouncer)), .5f, deltaTime);
					itBo++;
				}
				while (itO != obstacles.end())
				{
					(*(*itB)).BounceBall(Collision::CircleToRectangle((*(*itB)).ball, (*(*itO)).wall), .5f, deltaTime);
					itO++;
				}
				while (itF != flippers.end()) {
					(*(*itB)).BounceBall(Collision::CircleToOrientedRectangle((*(*itB)).ball, (*(*itF)).flipperShape), 1.f, deltaTime);
					if (Collision::CircleToOrientedRectangle((*(*itB)).ball, (*(*itF)).flipperShape).isColliding) {
						if (downGravity && (*(*itF)).player1) {
							downGravity = !downGravity;
							(*(*itB)).gravity *= -1;
						}
						if (!downGravity && !(*(*itF)).player1){
							downGravity = !downGravity;
							(*(*itB)).gravity *= -1;
						}
					}
					
					itF++;
				}
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
			}
			if(ball.ball.getPosition().y < 0 + ball.ball.getRadius())
			{
				manager.UpdateScore(true, ball);
				manager.RepoBall(ball);
				if (manager.scoreJ1 > 9)
				{
					j1Won = true;
					manager.Winner(true);
					isStarting = false;
				}
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

			manager.UpdateUI();
			manager.DrawUI(window);
		}
		else if (j1Won||j2Won)
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
