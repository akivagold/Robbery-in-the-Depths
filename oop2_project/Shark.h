#pragma once
//---- include section ------
#include <string>
#include "NPC.h"

//---- using section --------
using std::string;

/*
 * Shark class
 */
class Shark
	: public NPC
{
public:
	// constructor
	explicit Shark(sf::RenderWindow& window, GameScreen& gameScreen, int numOfLife = 0);
	// convert to string
	virtual string toString() const override { return "Shark: { " + NPC::toString() + " }"; };
private:
	// TODO play();
};


