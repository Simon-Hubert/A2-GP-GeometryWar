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

using namespace Collision;
constexpr float cubeSpeed = 500.f;
int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Geometry Wars");
	window.setVerticalSyncEnabled(true);

	// Début de la boucle de jeu
	bool isStarting = false;
	bool downGravity = true;
	Menu menu;
	sf::Clock frameClock;
	Ball ball;
	Player player1, player2;
	Bounce bounce, bounce2;
	Obstacle wall;

	player1.Init(sf::Vector2f(640, 600), true);
	player2.Init(sf::Vector2f(640, 120), false);
	ball.InitBall();
	wall.InitWall(sf::Color::Red, sf::Vector2f(-550, 400), sf::Vector2f(150, 50));
	bounce.InitBounce(sf::Color::Red, sf::Vector2f(-600, 400));
	bounce.InitBounce(sf::Color::Magenta, sf::Vector2f(200, 600));
	bounce2.InitBounce(sf::Color::Blue, sf::Vector2f(1000, 460));
	wall.InitWall(sf::Color::White, sf::Vector2f(300, 400), sf::Vector2f(100, 50));

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
					Collision::CollisionInfo col = Collision::CircleToOrientedRectangle((*(*itB)).ball, (*(*itF)).flipperShape);
					if (col.isColliding) {
						if (downGravity && (*(*itF)).player1) {
							downGravity = !downGravity;
							(*(*itB)).gravity *= -1;
						}
						if (!downGravity && !(*(*itF)).player1){
							downGravity = !downGravity;
							(*(*itB)).gravity *= -1;
						}
						float mul = (*(*itF)).getLinearSpeed((*(*itB)).ball.getPosition())/10.f;
						std::cout << mul << std::endl;
						(*(*itB)).BounceBall(col, mul, deltaTime);
					}
					
					itF++;
				}
				(*(*itB)).MoveBall(deltaTime);
				itB++;
			}
			//ball.BounceBall(bounce.Bouncing(Collision::CircleToCircle(ball.ball, bounce.bouncer)), .5f, deltaTime);
			//ball.BounceBall(bounce2.Bouncing(Collision::CircleToCircle(ball.ball, bounce2.bouncer)), .5f, deltaTime);
			//ball.BounceBall(Collision::CircleToRectangle(ball.ball, wall.wall), .5f, deltaTime);

			//ball.MoveBall(deltaTime);
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
			
		}
		else 
		{
			menu.DrawMenu(window);
		}

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
