#include "PowerUp.h"

void Item::CallPowerUp(bool &isItem, float deltaTime) {
	float PowerUpCooldown = 3.f;
	int Probability = rand() % 100;
	chrono += deltaTime;
	if (chrono >= PowerUpCooldown && isItem == false && Probability >= 0 && Probability <= 25) {
		InitItem();
		isItem = true;
		chrono = 0;
	}
	//int Probability = rand() % 100;
	//if (Probability >= 0 && Probability <= 25 ) {
	//	InitItem();
	//	isItem = true;
	//}
	
}

Item Item::InitItem()
{
	int radius = 25;
	item.setFillColor(sf::Color::Green);
	item.setPosition(rand() % 1280, rand() % 720);
	//item.setPosition(600, 500);
	item.setRadius(radius);
	item.setOrigin(radius, radius);
	return *this;
}

void Item::DrawItem(sf::RenderWindow& window)
{
	window.draw(item);
}

void Item::DestroyItem(bool &isItem, float deltaTime, bool collision, Ball ball) {
	if (isItem == true) {
		float LifeTimePowerUp = 6.f;
		chrono += deltaTime;
		chronokill += deltaTime;
		if (collision == true) {
			CollisionItem(ball);
			FalseInitItem();
			isItem = false;
			chrono = 0;
			chronokill = 0;
		}
		if (chronokill >= LifeTimePowerUp) {
			FalseInitItem();
			isItem = false;
				chrono = 0;
			chronokill = 0;
		}
	}
}

Item Item::FalseInitItem()
{
	int radius = 25;
	item.setFillColor(sf::Color::Green);
	item.setPosition(1243, 2134);
	item.setRadius(radius);
	item.setOrigin(radius, radius);
	return *this;
}


void Item::Powerup1(Ball &ball) {
	ball.speed.x *= 6.f;
	ball.speed.y *= 6.f;
	std::cout << "dw,nfkhisfodh" << std::endl;
}

void Item::Powerup2() {

}

void Item::CollisionItem(Ball &ball) {
	int Powerup = rand() % 1;

	if (Powerup == 0) {
		Powerup1(ball);
	} if (Powerup == 1) {
		//Powerup2();
	}
}