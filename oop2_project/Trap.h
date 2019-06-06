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
	// convert to string
	virtual string toString() const override { return "Trap { " + InteractableObject::toString() + " }"; }
	// draw
	virtual void draw() override;
	// play
	virtual void play() = 0;
protected:
	// constructor
	explicit Trap(GameScreen& gameScreen);
};

