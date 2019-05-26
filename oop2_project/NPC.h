#pragma once
//---- include section ------
#include <string>
#include "Character.h"

//---- using section --------
using std::string;

/*
 * NPC class
 */
class NPC
	: public Character
{
public:
	// constructor
	explicit NPC(sf::RenderWindow& window, GameScreen& gameScreen, int numOfLife = 0);
	// convert to string
	virtual string toString() const override { return "NPC: { " + Character::toString() + " }"; };
};


