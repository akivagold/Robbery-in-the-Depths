#include "Grenade.h"
#include "Explosion.h"
#include "GameScreen.h"
#include "Box.h"

// init
const sf::Vector2f Grenade::ACCELERATION(0.0002f, 0.0001f);

Grenade::Grenade(GameScreen& gameScreen, Character* owner, float upAmplitude)
	: Projectile(gameScreen, owner)
{
	getSpeed().y = -upAmplitude;
	init();
}

void Grenade::onJoinedGame()
{
	Projectile::onJoinedGame();
	GUI::SoundManager::getInterface().playSound("gl_fire");
}

void Grenade::explode()
{
	Projectile::explode();

	// create explosion
	std::shared_ptr<Explosion> explosion = std::make_shared<Explosion>(getGameScreen());
	sf::Vector2f myCenter = getCenter();
	explosion->setPosition(myCenter.x - explosion->getSize().x / 2.f, myCenter.y - explosion->getSize().y / 2.f);
	getGameScreen().getWorld().getBODS().requestAddBO(explosion);
}

void Grenade::onCollide(Box* box)
{
	box->decreaseDurabilityState(getDamage());
	explode();
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
	if (Character::isLeftDirections(getDirection()))
		getInteralAcceleration().x = -ACCELERATION.x*getSize().x;
	else
		getInteralAcceleration().x = ACCELERATION.x*getSize().x;
	getInteralAcceleration().y = ACCELERATION.y*getSize().y;
}
