#pragma once
//---- include section ------
#include <string>
#include "GameScreen.h"
#include "StaticObject.h"
class Projectile;

//---- using section --------
using std::string;

/*
 * Box class
 */
class Box :
	public StaticObject
{
public:
	// constructor
	explicit Box(GameScreen& gameScreen, int durabilityState = DEFAULT_DURABILITY);
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const override { return false; }
	// get durability state
	int getDurabilityState() const { return m_durabilityState; }
	// decrease durability state
	void decreaseDurabilityState(int relDS);
	// set durability state
	void setDurabilityState(int durabilityState);
	// destroy
	void destroy();
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
	virtual string toString() const override { return "Box: { " + StaticObject::toString() + " }"; }
private:
	// char
	static const char CHAR = 'b';
	// draw priority
	static const int DRAW_PRIORITY = 6;
	// register flag in BOFactory
	static bool isRegistered;
	// default durability
	static const int DEFAULT_DURABILITY = 5;
	// durability state
	int m_durabilityState;
	// init
	void init();
	// check if durability state is legal
	bool isLegalDurabilityState(int durabilityState) const { return (durabilityState >= 0); }
	using StaticObject::vanish;
};

