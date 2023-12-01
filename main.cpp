#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include <iostream>

constexpr float cubeSpeed = 500.f;

int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars");
	window.setVerticalSyncEnabled(true);
	Player player;

	player.Init();

	sf::Clock frameClock;

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
		player.Update(deltaTime);



		// Affichage
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		player.Draw(window);

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
