#include "Bullet.h"


const sf::Vector2f Bullet::ACCELERATION = sf::Vector2f(0.0001f*Bullet::getMODefSize().x, 0.0001f*Bullet::getMODefSize().y);

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
		getInteralAcceleration().x = ACCELERATION.x;
	}
	else if(getDirection() == Direction::LEFT) {
		getInteralAcceleration().x = -ACCELERATION.x;
	}
	else if (getDirection() == Direction::UP) {
		getInteralAcceleration().y = -ACCELERATION.y;
	}
	else
		getInteralAcceleration().y = ACCELERATION.y;
}

void Bullet::init()
{
	if(getDirection() == Direction::RIGHT || getDirection() == Direction::LEFT)
		setAnimation("bullet_horizontal");
	else if(getDirection() == Direction::UP)
		setAnimation("bullet_up");
	else if (getDirection() == Direction::DOWN)
		setAnimation("bullet_down");
	
	if (getDirection() == Direction::LEFT) {
		flipAnimation();
	}
	setDamage(DAMAGE);
}
