#pragma once
//---- include section ------
#include <string>
#include "MovingObject.h"
#include "Character.h"
#include "StopWatch.h"

//---- using section --------
using std::string;

/*
 * Projectile class
 */
class Projectile :
	public MovingObject
{
public:
	// draw
	virtual void draw() override;
	// explode
	virtual void explode();
	// check if is in shot time
	bool isInShotTime() const { return m_inShot; }
	// get my owner
	Character* getMyOwner() { return m_owner; }
	// convert to string
	virtual string toString() const override { return "Projectile { " + MovingObject::toString() + " }"; }
protected:
	// constructor
	explicit Projectile(GameScreen& gameScreen, Character* owner);
	// event when direction changed
	virtual void onDirectionChanged() override { }
	// event when object joined to game
	virtual void onJoinedGame() override;
private:
	// draw priority
	static const int DRAW_PRIORITY = 22;
	// relative position from owner
	static const float REL_POS_OWNER;
	// shot time
	static const int SHOT_TIME = 30;
	// my owner
	Character* m_owner;
	// in shot stopWatch
	StopWatch m_inShotSW;
	// in shot flag
	bool m_inShot;
	// init
	void init();
	// disable suicide (use explode intand)
	using MovingObject::suicide;
};

