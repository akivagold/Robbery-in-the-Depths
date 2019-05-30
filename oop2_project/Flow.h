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
	void init();
	virtual void onCollide(const std::shared_ptr<MovingObject>& obj) override;
	virtual bool canMoveThroughMe() const override { return true; };
private:
	// angle & power
	float m_flowAngle, m_flowPower;
};

