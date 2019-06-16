#pragma once
//---- include section ------
#include <string>
#include "InteractableObject.h"
#include "MovingObject.h"

//---- using section --------
using std::string;

/*
 * Trap class
 */
class Trap :
	public InteractableObject
{
public:
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override { return "Trap: { " + InteractableObject::toString() + " }"; }
protected:
	// constructor
	explicit Trap(GameScreen& gameScreen);
	// play
	virtual void play() = 0;
};

