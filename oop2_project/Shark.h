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
	explicit Shark(GameScreen& gameScreen, int numOfLife = 0);
	// event when direction changed
	virtual void onDirectionChanged() override {}; // TODO: use this
	// convert to string
	virtual string toString() const override { return "Shark: { " + NPC::toString() + " }"; }	
protected:
	// play
	//virtual void play() override {}				// TODO
	// the object choose where to go
	virtual void playChoice() override;       // TODO
private:
	// init
	void init();
	// radius attak
	float m_radiusAttak;
	
	
};


