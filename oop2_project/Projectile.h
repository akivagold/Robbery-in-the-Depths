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
	// event when object joined to game
	virtual void onJoinedGame() override;
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override { return "Projectile { " + MovingObject::toString() + " }"; }
	// explode
	virtual void explode();
	// check if is in shot time
	bool isInShotTime() const { return m_inShot; }
	// get my owner
	Character* getMyOwner() { return m_owner; }
protected:
	// constructor
	explicit Projectile(GameScreen& gameScreen, Character* owner);
	// event when direction changed
	virtual void onDirectionChanged() override { }
	using MovingObject::suicide;
private:
	// draw priority
	static const int DRAW_PRIORITY = 22;
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
};

