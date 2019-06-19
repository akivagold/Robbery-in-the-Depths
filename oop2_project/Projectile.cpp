#include "Projectile.h"

void Projectile::onJoinedGame()
{
	m_inShotSW.start(SHOT_TIME, [this] {
		m_inShot = false;
	});
}

void Projectile::draw()
{
	MovingObject::draw();
	m_inShotSW.checkStopWatch();
}

void Projectile::explode()
{
	suicide();
}

Projectile::Projectile(GameScreen& gameScreen, Character* owner)
	: MovingObject(gameScreen), m_owner(owner), m_inShot(true)
{
	init();
}

void Projectile::init()
{
	setSize(static_cast<int>(BoardObject::getDefaultSize().x*0.3f), static_cast<int>(BoardObject::getDefaultSize().y*0.3f));
	if (Character::isLeftDirections(getMyOwner()->getDirection()))
		setPosition(getMyOwner()->getPosition().x - getSize().x, getMyOwner()->getCenter().y - getSize().y / 2.f);
	else if (Character::isRightDirections(getMyOwner()->getDirection()))
		setPosition(getMyOwner()->getPosition().x + getMyOwner()->getSize().x, getMyOwner()->getCenter().y - getSize().y / 2.f);
	else if (Character::isUpDirections(getMyOwner()->getDirection()))
		setPosition(getMyOwner()->getCenter().x - getSize().x / 2.f, getMyOwner()->getPosition().y - getSize().y);
	else
		setPosition(getMyOwner()->getCenter().x - getSize().x / 2.f, getMyOwner()->getPosition().y + getMyOwner()->getSize().y);

	setDrawPriority(DRAW_PRIORITY);
	getSpeed().x = getMyOwner()->cGetSpeed().x;
	setDirection(getMyOwner()->getDirection());
}

