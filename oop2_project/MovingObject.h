#pragma once
//---- include section ------
#include <string>
#include "InteractableObject.h"

//---- using section --------
using std::string;

/*
 * MovingObject class
 */
class MovingObject
	:public InteractableObject
{
public:
	// constructor
	MovingObject() = default;
	// TODO 
	/*void suicide();
	void play();*/
	virtual string toString() const override { "MovingObject: {" + InteractableObject::toString() + " }"; }
private:
	sf::Vector2f m_speed, m_interalAcceleration, m_externalAcc;
	//sf::Vector2f getNextPosition();
	Timer m_timer;
};

