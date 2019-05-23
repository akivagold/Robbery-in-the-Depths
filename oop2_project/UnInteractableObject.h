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
	:public BoardObject
{
public:
	// constructor
	UnInteractableObject() = default;
	// convert to string
	virtual string toString() const override { return "UnInteractableObject: {" + BoardObject::toString() + "}"; }
private:

};

