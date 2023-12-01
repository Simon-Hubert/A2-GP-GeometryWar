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
	}
	else {
		maxAngle = 360 - maxAngle;
		flipperShape.setRotation(359);
	}

	flipperShape.setFillColor(sf::Color::Red);
	flipperShape.setSize(size);
	flipperShape.setPosition(posX, pos.y);
	flipperShape.setOrigin(originX, size.y / 2);
}

void Flipper::Update(float deltaTime)
{
	float angleFrac = deltaTime * speed;
	if (sf::Keyboard::isKeyPressed(input)) {
		if (isDroit)
		{
			flipperShape.rotate(angleFrac);
			float angle = flipperShape.getRotation();
			angle = angle > maxAngle ? maxAngle : angle;
			flipperShape.setRotation(angle);
		}
		else
		{
			flipperShape.rotate(-angleFrac);
			float angle = flipperShape.getRotation();
			angle = angle < maxAngle ? maxAngle : angle;
			flipperShape.setRotation(angle);
		}
	}
	else {
		if (isDroit)
		{
			float angle = flipperShape.getRotation();
			angle - angleFrac < 0 ? angleFrac = angleFrac - abs(angle - angleFrac) : angleFrac;
			flipperShape.rotate(-angleFrac);
		}
		else
		{
			float angle = flipperShape.getRotation();
			if (angle != 0) {
				angle + angleFrac > 360 ? angleFrac = 360 - angle : angleFrac;
				flipperShape.rotate(angleFrac);
			}
		}
	}
}

void Flipper::Draw(sf::RenderWindow& window)
{
	window.draw(flipperShape);
}
