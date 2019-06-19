#pragma once
//---- include section ------
#include <string>
#include "InteractableObject.h"
#include "StopWatch.h"

//---- using section --------
using std::string;

/*
 * Explosion class
 */
class Explosion 
	: public InteractableObject
{
public:
	// constructor
	explicit Explosion(GameScreen& gameScreen, float power = DEFAULT_POWER);
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const override { return true; }
	// draw
	virtual void draw() override;
	// set power
	void setPower(float power) { m_power = power; }
	// get power
	float getPower() const { return m_power; }
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) override { obj->onCollide(this); }
	virtual void onCollide(Player* player) override {}
	virtual void onCollide(Shark* shark) override {}
	virtual void onCollide(Crab* crab) override {}
	virtual void onCollide(Rubber* rubber) override {}
	virtual void onCollide(Chest* chest) override {}
	virtual void onCollide(Wall* wall) override {}
	virtual void onCollide(Flow* flow) override {}
	virtual void onCollide(Bullet* bullet) override {}
	virtual void onCollide(MachineGun* machineGun) override {}
	virtual void onCollide(Grenade* grenade) override {}
	virtual void onCollide(Explosion* explosion) override {}
	virtual void onCollide(Box* box) override {}
	virtual void onCollide(ExitLevel* exitLevel) override {}
	// convert to string
	virtual string toString() const override { return "Explosion: { " + InteractableObject::toString() + " }"; }
protected:
	// event when object joined to game
	virtual void onJoinedGame() override;
private:
	// draw priority
	static const int DRAW_PRIORITY = 150;
	// damage
	static const int DAMAGE = 0;
	// animation frequency
	static const int ANIM_FREQUENCY = 15;
	// time to show
	static const int SHOW_TIME = 1000;
	// default power
	static const float DEFAULT_POWER;
	// power of explosion
	float m_power;
	// vanish stopWatch
	StopWatch m_vanishSW;
	// init
	void init();
};

