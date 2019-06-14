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
	virtual void onCollide(ExitLevel* exitLevel) override {} // TODO use this
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

