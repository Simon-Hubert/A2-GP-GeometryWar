#include "PowerUp.h"

void Item::CallPowerUp(bool* isItem) {
	int powerUp = rand() % 3;

	if (powerUp == 0) {
		std::cout << "sdknvksbdjknksodklsdgnkgshn;klfdnklb d" << std::endl;
		InitItem();
		*(isItem) = true;
	}
}

void Item::CreatePowerUp() {
	Item item;
	item.InitItem();
}

Item Item::InitItem()
{
	int radius = 25;
	item.setFillColor(sf::Color::Green);
	item.setPosition(rand() % 1280, rand() % 720);
	item.setRadius(radius);
	item.setOrigin(radius, radius);
	return *this;
}

void Item::DrawItem(sf::RenderWindow& window)
{
	window.draw(item);
}

void Item::DestroyItem(bool* isItem) {
	FalseInitItem();
	*(isItem) = false;
}

Item Item::FalseInitItem()
{
	int radius = 25;
	item.setFillColor(sf::Color::Green);
	item.setPosition(12432414, 213413532);
	item.setRadius(radius);
	item.setOrigin(radius, radius);
	return *this;
}
