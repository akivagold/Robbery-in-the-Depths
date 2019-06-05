#include "HotWeapon.h"

void HotWeapon::setAmmo(int ammo)
{
	if (ammo < 0)
		throw std::out_of_range("Cannot set ammo quantity " + std::to_string(ammo) + " less then zero");
	setUseLimit(ammo);
}

void HotWeapon::useTool()
{
	Weapon::useTool();
	fire();
}


string HotWeapon::toString() const
{
	return "HotWeapon: { " + Weapon::toString() + " }";
}

HotWeapon::HotWeapon(Character* object, int ammo)
	: Weapon(object)
{
	setAmmo(ammo);
}
