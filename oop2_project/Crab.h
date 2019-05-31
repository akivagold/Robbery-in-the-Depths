#pragma once
//---- include section ------
#include <string>
#include "NPC.h"

//---- using section --------
using std::string;

/*
 * Crab class
 */
class Crab
	: public NPC
{
public:
	// char
	static const char CHAR = 'c';
	// constructor
	explicit Crab(GameScreen& gameScreen, int numOfLife = 0);
	// event when direction changed
	virtual void onDirectionChanged() override {}; // TODO: use this
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override { return "Crab: { " + NPC::toString() + " }"; }
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
private:
	// draw priority
	static const int DRAW_PRIORITY = 20;
	// minimum radius to see the player
	static const float MIN_PLAYER_RADIUS;
	// flag that check if player in crab radius
	bool m_isPlayerInRadius;
	// timer
	Timer m_timer;
	// init
	void init();	
};

