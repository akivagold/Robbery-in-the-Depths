#pragma once
//---- include section ------
#include "HotWeapon.h"

//---- using section --------
using std::string;

/*
 * AK47 class
 */
class AK47 :
	public HotWeapon
{
public:
	// constructor
	explicit AK47(Character* owner, int ammo = DEFAULT_AMMO);
	// get tool type
	virtual ToolType getToolType() const override { return ToolType::TT_AK47; }
	// get tool name
	virtual string getToolName() const override { return "ak47"; }
	// convert to string
	virtual string toString() const override;
	// get default use limit
	virtual int getDefUseLimit() const override { return DEFAULT_AMMO; }
	// fire
	virtual void fire() override;
private:
	// defualt ammo
	static const int DEFAULT_AMMO = 30;
	// init
	void init();
};

