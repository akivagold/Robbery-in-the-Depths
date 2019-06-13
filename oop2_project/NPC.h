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
	// convert to string
	virtual string toString() const override { return "NPC: { " + Character::toString() + " }"; }
	// get ranodm up directions
	static Direction getRandomUPDirections();
	// get ranodm right directions
	static Direction getRandomRightDirections();
	// get ranodm down directions
	static Direction getRandomDownDirections();
	// get ranodm left directions
	static Direction getRandomLeftDirections();
	// set new direction after collid
	void setDirectionAfterCollid(Direction direction);
	// go by direction	
	void goByDirection(Direction direction);
	// get radius from player
	float getRadiusFromPlayer() const;
protected:
	// constructor
	explicit NPC(GameScreen& gameScreen, int numOfLife = 0);
};
