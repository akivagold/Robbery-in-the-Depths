#pragma once
//---- include section ------
#include <string>
#include "BoardObject.h"

//---- using section --------
using std::string;

/*
 * UnInteractableObject class
 */
class UnInteractableObject
	: public BoardObject
{
public:
	// convert to string
	virtual string toString() const override { return "UnInteractableObject: {" + BoardObject::toString() + "}"; }
protected:
	// constructor
	using BoardObject::BoardObject;
};

