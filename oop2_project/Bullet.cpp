#include "Bullet.h"


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
		getInteralAcceleration().x = 0.0004f;
	}
	else {
		getInteralAcceleration().x = -0.0004f;
	}
}

void Bullet::init()
{
	//m_lastDirection = getDirection();
	setAnimation("bullet");
	if (getDirection() == Direction::LEFT) {
		flipAnimation();
	}
}
