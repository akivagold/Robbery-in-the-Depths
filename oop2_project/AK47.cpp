#include "AK47.h"



AK47::AK47(std::shared_ptr<MovingObject>& object)
	: HotWeapon(object)
{
	init();
}

string AK47::toString() const
{
	return "AK47: { " + HotWeapon::toString() + " } ";
}

#include <iostream>
void AK47::fire()
{
	// create bullet
	std::cout << "crate Bullet" << std::endl;
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(getMyowner()->getGameScreen(), getMyowner()->getDirection());
	bullet->getGameScreen().getWorld().getBODS().requestAddBO(bullet);
	bullet->setPosition(getMyowner()->getPosition()); //TODO: + self size
	setAmmo(getAmmo() - 1);
}

void AK47::init()
{
	setToolName("AK47");
	setAmmo(20);
}
