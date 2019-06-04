#pragma once
#include "Tool.h"

/*
 * Weapon class
 */
class Weapon :
	public Tool
{
public:
	// number of weapons
	static const int NUM_OF_WEAPONS = 1;
	// weapon type
	enum WeaponType { AK47 };
	// random weapon
	static WeaponType randWeapon();
	// convert to string
	virtual string toString() const override { return "Weapon: { " + Tool::toString() + " }"; }
protected:
	// constructor
	using Tool::Tool;	
};

