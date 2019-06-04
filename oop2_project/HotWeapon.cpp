#include "HotWeapon.h"


void HotWeapon::setAmmo(int ammo)
{
	if (ammo < 0)
		throw std::out_of_range("cannot set ammo quantity " + std::to_string(ammo) + " less then zero");
	m_ammo = ammo;
}

void HotWeapon::useTool()
{
	if (!canUsingTool())
		throw std::logic_error("Cannot use weapon without ammo!");
	fire();
}


string HotWeapon::toString() const
{
	return "HotWeapon: { ammo=" + std::to_string(m_ammo) + ", " + Weapon::toString() + " }";
}

HotWeapon::HotWeapon(Character* object)
	: Weapon(object)
{}
