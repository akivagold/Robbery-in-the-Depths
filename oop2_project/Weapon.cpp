#include "Weapon.h"

Weapon::WeaponType Weapon::randWeapon()
{
	return static_cast<WeaponType>(rand()%NUM_OF_WEAPONS);
}
