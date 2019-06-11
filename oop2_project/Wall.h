#pragma once
//---- include section ------
#include <string>
#include "GameScreen.h"
#include "UnInteractableObject.h"

//---- using section --------
using std::string;

/*
 * Wall class
 */
class Wall
	: public UnInteractableObject
{
public:
	// char
	static const char CHAR = 'w';
	// constructor
	explicit Wall(GameScreen& gameScreen);
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const override { return false; }
	// convert to string
	virtual string toString() const override;
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) override { obj->onCollide(this); }
	virtual void onCollide(Player* player) override {} // TODO use this
	virtual void onCollide(Shark* shark) override {} // TODO use this
	virtual void onCollide(Crab* crab) override {} // TODO use this
	virtual void onCollide(Rubber* rubber) override {} // TODO use this
	virtual void onCollide(Chest* chest) override {} // TODO use this
	virtual void onCollide(Wall* wall) override {} // TODO use this
	virtual void onCollide(Flow* flow) override {} // TODO use this
	virtual void onCollide(Bullet* bullet) override {} // TODO use this
	virtual void onCollide(MachineGun* machineGun) override {} // TODO use this
	virtual void onCollide(Grenade* grenade) override {} // TODO use this
	virtual void onCollide(Explosion* explosion) override {}  // TODO use this
private:
	// draw priority
	static const int DRAW_PRIORITY = 5;
	// register flag in BOFactory
	static bool isRegistered;
	// init
	void init();
};

