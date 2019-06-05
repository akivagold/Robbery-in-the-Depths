#pragma once
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
	explicit AK47(Character* owner);
	// get tool type
	virtual ToolType getToolType() const override { return ToolType::TT_AK47; }
	// get tool name
	virtual string getToolName() const { return "ak47"; }
	// convert to string
	virtual string toString() const override;
	// fire
	virtual void fire() override;
private:
	// init
	void init();
};

