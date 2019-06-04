#pragma once
#include "Tool.h"

/*
 * Weapon class
 */
class Weapon :
	public Tool
{
public:
	// convert to string
	virtual string toString() const override { return "Weapon: { " + Tool::toString() + " }"; }
protected:
	// constructor
	using Tool::Tool;	
};

