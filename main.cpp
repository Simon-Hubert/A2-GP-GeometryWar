#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Ball.h"
#include "Bounce.h"
#include "Obstacle.h"
#include "Collision.h"
#include "Player.h"

using namespace Collision;

constexpr float cubeSpeed = 500.f;
int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars");
	window.setVerticalSyncEnabled(true);

	// Début de la boucle de jeu

	sf::Clock frameClock;
	Ball ball;
	Bounce bounce1;
	Obstacle wall;
	Player player;
	wall.InitWall(sf::Color::Red, sf::Vector2f(-550, 400), sf::Vector2f(150,50));
	wall.wall.rotate(30);
	bounce1.InitBounce(sf::Color::Red, sf::Vector2f(-600, 400));
	ball.InitBall();
	player.Init();


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
		//std::cout << 1.f / deltaTime << " FPS" << std::endl;

		// Logique
		//std::cout << ball.pos.x << ball.pos.y << "\n";
		
		//std::cout << Collision::CircleToCircle(ball.ball, bounce.bouncer).normal.x << Collision::CircleToCircle(ball.ball, bounce.bouncer).normal.y << std::endl;
		player.Update(deltaTime);
		ball.UpdateBall(deltaTime);
		ball.BounceBall(Collision::CircleToOrientedRectangle(ball.ball, player.getFlipper(true).flipperShape),.5f,deltaTime);
		ball.BounceBall(Collision::CircleToOrientedRectangle(ball.ball, player.getFlipper(false).flipperShape),.5f,deltaTime);
		ball.BounceBall(Collision::CircleToOrientedRectangle(ball.ball, wall.wall),.5f,deltaTime);

		ball.BounceBall(Collision::CircleToCircle(ball.ball, bounce1.bouncer), .5f, deltaTime);
		ball.MoveBall(deltaTime);

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		//window.draw(rectangle);
		ball.DrawBall(window);
		wall.DrawWall(window);
		bounce1.DrawBounce(window);
		player.Draw(window);
		// On présente la fenêtre sur l'écran
		window.display();
	}
}
