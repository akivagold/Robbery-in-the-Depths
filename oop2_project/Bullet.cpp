#include "Bullet.h"
#include "SoundManager.h"
#include "Box.h"

const sf::Vector2f Bullet::ACCELERATION = sf::Vector2f(0.0001f*Bullet::getMODefSize().x, 0.0001f*Bullet::getMODefSize().y);

Bullet::Bullet(GameScreen& gameScreen, Character* owner)
	: Projectile(gameScreen, owner), m_collideWithMyOwner(true)
{
	init();
}

void Bullet::onJoinedGame()
{
	Projectile::onJoinedGame();
	playSound("bullet_fire", 1.f, 30.f);
}

void Bullet::explode()
{
	Projectile::explode();
}

void Bullet::draw()
{
	Projectile::draw();
	m_time.checkTimer();
}


void Bullet::onCollide(Box* box)
{
	box->decreaseDurabilityState(getDamage());
	explode();
}

void Bullet::playChoice(Direction lastDirection, bool isCollided)
{
	if (isCollided && !m_collideWithMyOwner) {
		explode();
		return;
	}

	// check if collide with his owner 
	if (!getBound().intersects(getMyOwner()->getBound()))
		m_collideWithMyOwner = false;
	else
		m_collideWithMyOwner = true;

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
	else {
		getInteralAcceleration().y = ACCELERATION.y;
	}		
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

	m_time.start(900, [this] {
		explode();
	});
}
