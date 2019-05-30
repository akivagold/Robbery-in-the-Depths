#pragma once
//---- include section ------
#include <string>
#include "GameScreen.h"
#include "UnInteractableObject.h"

//---- using section --------
using std::string;

/*
 * Wall class
 */
class Wall
	: public UnInteractableObject
{
public:
	// constructor
	explicit Wall(GameScreen& gameScreen);
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const { return false; }
	// convert to string
	virtual string toString() const override;
private:
	// init
	void init();
};

