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
	int getAmmo() { return m_ammo; }
	// use tool
	virtual void useTool() override;
	// check if can use
	virtual bool canUsingTool() override { return (m_ammo > 0); }
	//convert to string
	virtual string toString() const override;
protected:
	explicit HotWeapon(std::shared_ptr<BoardObject>& object);
	// fire bullet
	virtual void fire() = 0; 
private:
	// ammo quantity
	int m_ammo;

};

