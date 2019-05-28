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
	virtual string toString() const override { return "Shark: { " + NPC::toString() + " }"; }
	// play
	virtual void play() override {}				// TODO
protected:
	// the object choose where to go
	virtual void playChoice() override {}       // TODO
private:
	// init
	void init();
};


