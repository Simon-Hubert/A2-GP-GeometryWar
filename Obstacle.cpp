#include "Obstacle.h"


void Obstacle::InitWall(sf::Color color, sf::Vector2f pos, sf::Vector2f size)
{	
	wall.setSize(size);
	wall.setOrigin((size.x / 2), (size.y / 2));
	wall.setFillColor(color);
	wall.setPosition(pos);

}

void Obstacle::DrawWall(sf::RenderWindow& window)
{
	window.draw(wall);
}

