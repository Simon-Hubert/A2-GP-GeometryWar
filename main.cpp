#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Ball.h"
#include "Bounce.h"
#include "Obstacle.h"
#include "Collision.h"
#include "PowerUp.h"

using namespace Collision;

constexpr float cubeSpeed = 500.f;
int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars");
	window.setVerticalSyncEnabled(true);

	// Début de la boucle de jeu
	srand(time(NULL));
	float chrono = 0;
	float chronokill = 0;
	bool isItem = false;
	sf::Time time;
	sf::Clock frameClock;
	Ball ball;
	Bounce bounce, bounce2;
	Obstacle wall;
	Item item;
	ball.InitBall();
	bounce.InitBounce(sf::Color::Magenta, sf::Vector2f(620, 600));
	bounce2.InitBounce(sf::Color::Blue, sf::Vector2f(400, 460));
	wall.InitWall(sf::Color::White, sf::Vector2f(600, 700), sf::Vector2f(120, 50));


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
		ball.MoveBall(deltaTime, Collision::CircleToCircle(ball.ball, bounce.bouncer));
		ball.MoveBall(deltaTime, Collision::CircleToCircle(ball.ball, bounce2.bouncer));
		ball.MoveBall(deltaTime, Collision::CircleToRectangle(ball.ball, wall.wall));

		std::cout << Collision::CircleToCircle(ball.ball, bounce.bouncer).normal.x << Collision::CircleToCircle(ball.ball, bounce.bouncer).normal.y << std::endl;
		ball.BounceBall(bounce.Bouncing(Collision::CircleToCircle(ball.ball, bounce.bouncer)), .5f);
		ball.BounceBall(bounce2.Bouncing(Collision::CircleToCircle(ball.ball, bounce2.bouncer)), .5f);
		ball.BounceBall(Collision::CircleToRectangle(ball.ball, wall.wall), .2f);

		chrono += deltaTime;
		if (chrono >= 1 && isItem == false) {
			std::cout << "1 seconde" << std::endl;
			item.CallPowerUp(&isItem);
			chrono = 0;
		}
		if (isItem == true) {
			chronokill += deltaTime;
			if (chronokill >= 3) {
				item.DestroyItem(&isItem);
				chrono = 0;
				chronokill = 0;
			}
		}
		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		//window.draw(rectangle);
		ball.DrawBall(window);
		bounce.DrawBounce(window);
		bounce2.DrawBounce(window);
		wall.DrawWall(window);
		item.DrawItem(window);

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
