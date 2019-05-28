#pragma once
//---- include section ------
#include <string>
#include "InteractableObject.h"

//---- using section --------
using std::string;

/*
 * class StaticObject
 */
class StaticObject
	: public InteractableObject
{
public:
	// convert to string
	virtual string toString() const override { return "StaticObject: { " + InteractableObject::toString() + " }"; }
protected:
	// constructor
	explicit StaticObject(GameScreen& gameScreen);
};

