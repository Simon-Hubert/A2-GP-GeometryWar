#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Ball.h"

constexpr float cubeSpeed = 500.f;

int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars");
	window.setVerticalSyncEnabled(true);

	// Début de la boucle de jeu
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(640, 360);
	rectangle.setSize(sf::Vector2f(128, 128));

	sf::Clock frameClock;
	Ball ball;
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
		std::cout << "vitesse: " << ball.speed << std::endl;

		// Logique
		ball.MoveBall(deltaTime);

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		//window.draw(rectangle);
		ball.DrawBall(window);


		// On présente la fenêtre sur l'écran
		window.display();
	}
}
