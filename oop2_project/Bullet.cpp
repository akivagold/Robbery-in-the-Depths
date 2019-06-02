#include "Bullet.h"


Bullet::Bullet(GameScreen& gameScreen, Direction direction)
	: Projectile(gameScreen, direction)
{
	setDirection(direction);
	init();
}

void Bullet::playChoice(Direction lastDirection, bool isCollided)
{
	if (isCollided) {
		suicide();
		return;
	}

	// set speed
	if (getDirection() == Direction::RIGHT) {
		getInteralAcceleration().x = 0.0002f;
	}
	else {
		getInteralAcceleration().x = -0.0002f;
	}
}

void Bullet::init()
{
	if (getDirection() == Direction::RIGHT) {
		setAnimation("bullet");
	}
	else {
		setAnimation("bullet"); // TODO change direction
	}
}
