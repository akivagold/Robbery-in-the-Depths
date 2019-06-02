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
	// char
	static const char CHAR = 'w';
	// constructor
	explicit Wall(GameScreen& gameScreen);
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const override { return false; }
	// convert to string
	virtual string toString() const override;
private:
	// init
	void init();
};

