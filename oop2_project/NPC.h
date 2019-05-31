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
	explicit NPC(GameScreen& gameScreen, int numOfLife = 0);
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
	// check if is up directions
	static bool isUpDirections(Direction direct);
	// check if is right directions
	static bool isRightDirections(Direction direct);
	// check if is down directions
	static bool isDownDirections(Direction direct);
	// check if is left directions
	static bool isLeftDirections(Direction direct);
	// get radius from player
	float getRadiusFromPlayer() const;
};


