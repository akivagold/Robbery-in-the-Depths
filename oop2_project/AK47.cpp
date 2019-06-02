#include "AK47.h"
#include "Bullet.h"
#include "GameScreen.h"

AK47::AK47(std::shared_ptr<MovingObject>& owner)
	: HotWeapon(owner)
{
	init();
}

string AK47::toString() const
{
	return "AK47: { " + HotWeapon::toString() + " }";
}

void AK47::fire()
{
	// crate bullet
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(getMyOwner()->getGameScreen(), getMyOwner()->getDirection());
	bullet->getGameScreen().getWorld().getBODS().requestAddBO(bullet);
	bullet->setPosition(getMyOwner()->getPosition());
	setAmmo(getAmmo() - 1);
}

void AK47::init()
{
	setToolName("AK47");
	setAmmo(20); // TODO remove this
}
