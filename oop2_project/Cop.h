#pragma once
//---- include section ------
#include <string>
#include "NPC.h"

//---- using section --------
using std::string;

/*
 * Cop class
 */
class Cop
	: public NPC
{
public:
	// char
	static const char CHAR = 's';
	// constructor
	explicit Cop(GameScreen& gameScreen, int numOfLife = 0);
	// convert to string
	virtual string toString() const override { return "Cop: { " + NPC::toString() + " }"; }
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) override { obj->onCollide(this); }
	virtual void onCollide(Player* player) override {} // TODO use this
	virtual void onCollide(Shark* shark) override {} // TODO use this
	virtual void onCollide(Crab* crab) override {} // TODO use this
	virtual void onCollide(Cop* cop) override {} // TODO use this
	virtual void onCollide(Chest* chest) override {} // TODO use this
	virtual void onCollide(Wall* wall) override {} // TODO use this
	virtual void onCollide(Flow* flow) override;
	virtual void onCollide(Bullet* bullet) override {} // TODO use this
private:
	// TODO playChoise();
};


