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
	explicit MovingObject(sf::RenderWindow& window, GameScreen& gameScreen);
	// play
	virtual void play() = 0;
	// convert to string
	virtual string toString() const override { return "MovingObject: {" + InteractableObject::toString() + " }"; }
private:
	sf::Vector2f m_speed, m_interalAcceleration, m_externalAcc;
	//sf::Vector2f getNextPosition();
	Timer m_timer;
};

