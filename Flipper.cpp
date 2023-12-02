#include "Flipper.h"

void Flipper::Init(sf::Vector2f pos)
{
	float posX = pos.x - 120;
	float originX = size.x / 4;
	input = sf::Keyboard::Key::Q;
	
	if (isDroit) {
		posX = pos.x + 120;
		originX = 3 * size.x / 4;
		input = sf::Keyboard::Key::D;
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
	//if (!isDroit) std::cout << newRot << "\n";
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
