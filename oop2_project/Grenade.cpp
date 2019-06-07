#include "Grenade.h"
#include "Explosion.h"
#include "GameScreen.h"

// init
const sf::Vector2f Grenade::ACCELERATION(0.00007f, 0.00005f);

Grenade::Grenade(GameScreen& gameScreen, Character* owner, float upAmplitude, Direction direction)
	: Projectile(gameScreen, owner, direction)
{
	getSpeed().y = -upAmplitude;
	init();
}

void Grenade::onJoinedGame()
{
	// TODO play sound GUI::SoundManager::getInterface().playSound("?");
}

void Grenade::explode()
{
	// create explosion
	std::shared_ptr<Explosion> explosion = std::make_shared<Explosion>(getGameScreen());
	sf::Vector2f myCenter = getCenter();
	explosion->setPosition(myCenter.x - explosion->getSize().x/2.f, myCenter.y - explosion->getSize().y / 2.f);
	getGameScreen().getWorld().getBODS().requestAddBO(explosion);

	suicide();
}

void Grenade::playChoice(Direction lastDirection, bool isCollided)
{
	if (isCollided) {
		explode();
		return;
	}

	updateAcc();
}

void Grenade::init()
{
	setAnimation("grenade");
	setSize(static_cast<int>(getSize().x*0.5f), static_cast<int>(getSize().y*0.5f));
	setDamage(DAMAGE);
	updateAcc();
}

void Grenade::updateAcc()
{
	if (getDirection() == Direction::LEFT)
		getInteralAcceleration().x = ACCELERATION.x*getSize().x;
	else
		getInteralAcceleration().x = -ACCELERATION.x*getSize().x;
	getInteralAcceleration().y = ACCELERATION.y*getSize().y;
}
