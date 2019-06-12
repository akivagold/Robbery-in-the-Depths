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
	// char
	static const char CHAR = 'b';
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
	virtual void onCollide(Player* player) override {} // TODO use this
	virtual void onCollide(Shark* shark) override {} // TODO use this
	virtual void onCollide(Crab* crab) override {} // TODO use this
	virtual void onCollide(Rubber* rubber) override {} // TODO use this
	virtual void onCollide(Chest* chest) override {} // TODO use this
	virtual void onCollide(Wall* wall) override {} // TODO use this
	virtual void onCollide(Flow* flow) override {} // TODO use this
	virtual void onCollide(Bullet* bullet) override {}
	virtual void onCollide(MachineGun* machineGun) override {} // TODO use this
	virtual void onCollide(Grenade* grenade) override {}
	virtual void onCollide(Explosion* explosion) override {}  // TODO use this
	virtual void onCollide(Box* box) override {}  // TODO use this
private:
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

