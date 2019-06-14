#pragma once
//---- include section ------
#include "HotWeapon.h"

//---- using section --------
using std::string;

/*
 * GrenadeLauncher class
 */
class GrenadeLauncher :
	public HotWeapon
{
public:
	// constructor
	explicit GrenadeLauncher(Character* owner, int ammo = DEFAULT_AMMO);
	// get tool type
	virtual ToolType getToolType() const override { return ToolType::TT_GRENADE_LAUNCHER; }
	// get tool name
	virtual string getToolName() const override { return "grenade_launcher"; }
	// get default use limit
	virtual int getDefUseLimit() const override { return DEFAULT_AMMO; }
	// fire
	virtual void fire() override;
	// convert to string
	inline virtual string toString() const override;
private:
	// defualt ammo
	static const int DEFAULT_AMMO = 10;
	// init
	void init();
};

inline string GrenadeLauncher::toString() const
{
	return "GrenadeLauncher: { " + HotWeapon::toString() + " }";
}

