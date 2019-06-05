#include "Bullet.h"

const float Bullet::ACCELERATION = 0.0001f*Bullet::getMODefSize().x;

Bullet::Bullet(GameScreen& gameScreen, Character* owner, Direction direction)
	: Projectile(gameScreen, owner, direction)
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
		getInteralAcceleration().x = ACCELERATION;
	}
	else {
		getInteralAcceleration().x = -ACCELERATION;
	}
}

void Bullet::init()
{
	setAnimation("bullet");
	if (getDirection() == Direction::LEFT) {
		flipAnimation();
	}
}
