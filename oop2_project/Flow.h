#pragma once
//---- include section ------
#include <string>
#include "StaticObject.h"

//---- using section --------
using std::string;

/*
 * class Flow
 class
 */
class Flow
	:public StaticObject
{
public:
	// constructor
	explicit Flow(sf::RenderWindow& window, GameScreen& gameScreen);
	// convert to string
	virtual string toString() const override { return "Flow: {" + StaticObject::toString() + "}"; }
private:
	float m_angle, m_power;
};

