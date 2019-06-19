#pragma once
//---- include section ------
#include <string>
#include "GameScreen.h"
#include "StaticObject.h"

//---- using section --------
using std::string;

/*
 * Box class
 */
class ExitLevel :
	public StaticObject
{
public:
	// constructor
	explicit ExitLevel(GameScreen& gameScreen);
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const override { return true; }
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
	virtual string toString() const override { return "ExitLevel: { " + StaticObject::toString() + " }"; }
private:
	// char
	static const char CHAR = 'e';
	// draw priority
	static const int DRAW_PRIORITY = 2;
	// register flag in BOFactory
	static bool isRegistered;
	// init
	void init();
};

