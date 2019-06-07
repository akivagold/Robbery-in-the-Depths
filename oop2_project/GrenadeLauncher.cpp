#include "GrenadeLauncher.h"
#include "Grenade.h"
#include "GameScreen.h"

GrenadeLauncher::GrenadeLauncher(Character* owner, int ammo)
	: HotWeapon(owner, ammo)
{
	init();
}

void GrenadeLauncher::fire()
{
	float upAmplitude = 0.01f*getMyOwner()->getSize().x;
	std::shared_ptr<Grenade> grenade = std::make_shared<Grenade>(getMyOwner()->getGameScreen(), getMyOwner(), upAmplitude, getMyOwner()->getDirection());
	grenade->setPosition(getMyOwner()->getCenter().x, getMyOwner()->getPosition().y);
	getMyOwner()->getGameScreen().getWorld().getBODS().requestAddBO(grenade);
}

void GrenadeLauncher::init()
{ }
