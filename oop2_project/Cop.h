#pragma once
//---- include section ------
#include <string>
#include "NPC.h"

//---- using section --------
using std::string;

/*
 * Cop class
 */
class Cop
	: public NPC
{
public:
	// char
	static const char CHAR = 's';
	// constructor
	explicit Cop(GameScreen& gameScreen, int numOfLife = 0);
	// convert to string
	virtual string toString() const override { return "Cop: { " + NPC::toString() + " }"; }
private:
	// TODO playChoise();
};


