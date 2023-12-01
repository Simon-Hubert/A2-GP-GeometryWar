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
	Player player;
	player.Init();
	ball.InitBall();

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
		player.Update(deltaTime);
		ball.MoveBall(deltaTime, Collision::CircleToOrientedRectangle(ball.ball, player.getFlipper(true)->flipperShape));
		ball.MoveBall(deltaTime, Collision::CircleToOrientedRectangle(ball.ball, player.getFlipper(false)->flipperShape));

		ball.BounceBall(Collision::CircleToOrientedRectangle(ball.ball, player.getFlipper(false)->flipperShape), .5f, deltaTime);
		ball.BounceBall(Collision::CircleToOrientedRectangle(ball.ball, player.getFlipper(true)->flipperShape), .5f, deltaTime);
		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		//window.draw(rectangle);
		player.Draw(window);
		ball.DrawBall(window);

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
