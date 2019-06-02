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
	// collide event
	virtual void onCollide(MovingObject* obj) override;
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const override { return true; }
	// set power of flow
	void setFlowPower(const sf::Vector2f& flowPower) { m_flowPower = flowPower; }
	// get flow power
	const sf::Vector2f& getFlowPower() const { return m_flowPower; }
private:
	// angle & power
	sf::Vector2f m_flowPower;
	// init
	void init();
};

