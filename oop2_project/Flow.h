#pragma once
//---- include section ------
#include <string>
#include "StaticObject.h"

//---- using section --------
using std::string;

/*
 * class Flow
 */
class Flow
	: public StaticObject
{
public:
	// constructor
	explicit Flow(GameScreen& gameScreen);
	// convert to string
	virtual string toString() const override { return "Flow: { " + StaticObject::toString() + " }"; }
private:
	// angle & power
	float m_flowAngle, m_flowPower;
};

