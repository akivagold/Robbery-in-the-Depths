#include "AK47.h"


AK47::AK47(std::shared_ptr<BoardObject>& object)
	: HotWeapon(object)
{
	init();
}

string AK47::toString() const
{
	return "AK47: { " + HotWeapon::toString() + " } ";
}

void AK47::fire()
{
	// TODO
}

void AK47::init()
{
	setToolName("AK47");
	setAmmo(20);
}
