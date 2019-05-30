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
	virtual void onCollide(MovingObject* obj) override;
	virtual bool canMoveThroughMe() const override { return true; }
	void setFlowPower(sf::Vector2f flow) { m_flowPower = flow; }
private:
	// angle & power
	sf::Vector2f m_flowPower;
};

