#include "Flipper.h"

void Flipper::Init(sf::Vector2f pos, int largeur, sf::Keyboard::Key inputA, sf::Keyboard::Key inputB)
{
	float posX = pos.x - largeur;
	float originX = size.x / 4;
	input = inputA;
	
	if (isDroit) {
		posX = pos.x + largeur;
		originX = 3 * size.x / 4;
		input = inputB;
		speed = -speed;
	}
	else {
		float temp = -maxAngle;
		maxAngle = -baseAngle;
		baseAngle = temp;
	}

	flipperShape.setFillColor(sf::Color::Red);
	flipperShape.setSize(size);
	flipperShape.setPosition(posX, pos.y);
	flipperShape.setOrigin(originX, size.y / 2);
}

void Flipper::Update(float deltaTime)
{
	float angleFrac = deltaTime * speed;
	float rot = flipperShape.getRotation();
	rot = rot >= 180 ? rot - 360 : rot;
	angleFrac *= sf::Keyboard::isKeyPressed(input) ? -1.f : 1.f;
	float newRot = rot + angleFrac;
	if (!(newRot <= maxAngle)) {
		angleFrac = maxAngle - rot;
	}
	if (!(newRot >= baseAngle)) {
		angleFrac = baseAngle - rot;
	}
	flipperShape.rotate(angleFrac);
}

void Flipper::Draw(sf::RenderWindow& window)
{
	window.draw(flipperShape);
}

float Flipper::getLinearSpeed(sf::Vector2f point)
{
	float angle = flipperShape.getRotation();
	float testAngle = angle > 180 ? angle - 360 : angle;
	if (testAngle == maxAngle || testAngle == baseAngle) {
		return 0;
	}
	sf::Vector2f flipPos = flipperShape.getPosition();
	sf::Vector2f flipVect = sf::Vector2f(cos(angle * 6.28318 / 360), sin(angle * 6.28318 / 360));
	sf::Vector2f projected = (flipVect.x * (point.x - flipPos.x) + flipVect.y * (point.y - flipPos.y)) * flipVect;
	return sqrt(projected.x * projected.x + projected.y * projected.y);
}
