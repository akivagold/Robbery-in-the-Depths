#include "HotWeapon.h"


void HotWeapon::setAmmo(int ammo)
{
	if (ammo < 0)
		throw std::out_of_range("cannot set ammo quantity" + std::to_string(ammo) + " lees from zero");
	m_ammo = ammo;
}

void HotWeapon::useTool()
{
	if (!canUsingTool())
		throw std::logic_error("cannot use weapon without ammo!");
	fire();
}


string HotWeapon::toString() const
{
	return "HotWeapon: { " + Weapon::toString() + " } ";
}

HotWeapon::HotWeapon(std::shared_ptr<MovingObject>& object)
	: Weapon(object)
{}
