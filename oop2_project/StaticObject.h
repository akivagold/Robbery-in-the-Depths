#pragma once
//---- include section ------
#include <string>
#include "InteractableObject.h"

//---- using section --------
using std::string;

/*
 * class StaticObject
 class
 */
class StaticObject
	:public InteractableObject
{
public:
	// constructor
	explicit StaticObject(sf::RenderWindow& window, GameScreen& gameScreen);
	// convert to string
	virtual string toString() const override { return "StaticObject: {" + InteractableObject::toString() + "}"; }
};

