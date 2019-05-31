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
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override { return "Shark: { " + NPC::toString() + " }"; }
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
private:
	// init
	void init();
	// radius attack
	float m_radiusAttack;
	Timer m_time;
	bool m_inChase;
	
	
};


