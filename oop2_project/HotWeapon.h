#pragma once
//---- include section ------
#include <string>
#include "Weapon.h"

//---- using section --------
using std::string;

/*
 * HotWeapon class
 */
class HotWeapon :
	public Weapon
{
public:
	// set ammo
	void setAmmo(int ammo);
	// get ammo
	int getAmmo() const { return getUseLimit(); }
	// use tool
	virtual void useTool() override;
	// convert to string
	virtual string toString() const override;
protected:
	// constructor
	explicit HotWeapon(Character* object);
	// fire bullet
	virtual void fire() = 0; 
};

