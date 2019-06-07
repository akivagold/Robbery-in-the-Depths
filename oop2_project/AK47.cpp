#include "AK47.h"
#include "Bullet.h"
#include "GameScreen.h"

AK47::AK47(Character* owner, int ammo)
	: HotWeapon(owner, ammo)
{
	init();
}


string AK47::toString() const
{
	return "AK47: { " + HotWeapon::toString() + " }";
}

void AK47::fire()
{
	// create bullet
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(getMyOwner()->getGameScreen(), getMyOwner(), getMyOwner()->getDirection());
	bullet->getGameScreen().getWorld().getBODS().requestAddBO(bullet);

	if (Player::isLeftDirections(getMyOwner()->getDirection()))
		bullet->setPosition(getMyOwner()->getPosition().x - bullet->getSize().x, getMyOwner()->getCenter().y - bullet->getSize().y/2.f);
	else if(Player::isRightDirections(getMyOwner()->getDirection()))
		bullet->setPosition(getMyOwner()->getPosition().x + getMyOwner()->getSize().x, getMyOwner()->getCenter().y - bullet->getSize().y/2.f);
	else if (Player::isUpDirections(getMyOwner()->getDirection()))
		bullet->setPosition(getMyOwner()->getCenter().x - bullet->getSize().x / 2.f, getMyOwner()->getPosition().y - bullet->getSize().y / 2.f);
	else
		bullet->setPosition(getMyOwner()->getCenter().x - bullet->getSize().x / 2.f, getMyOwner()->getPosition().y + getMyOwner()->getSize().y);
}

void AK47::init()
{}
