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
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(getMyOwner()->getGameScreen(), getMyOwner());
	bullet->getGameScreen().getWorld().getBODS().requestAddBO(bullet);
}

void AK47::init()
{}
