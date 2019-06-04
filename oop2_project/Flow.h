#pragma once
//---- include section ------
#include <string>
#include "StaticObject.h"
#include "MovingObject.h"
#include "Player.h"
#include "Shark.h"
#include "Crab.h"


//---- using section --------
using std::string;

/*
 * class Flow
 */
class Flow
	: public StaticObject
{
public:
	// constructor
	explicit Flow(GameScreen& gameScreen);
	// convert to string
	virtual string toString() const override { return "Flow: { " + StaticObject::toString() + " }"; }
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const override { return true; }
	// get flow power
	const sf::Vector2f& getFlowPower() const { return m_flowPower; }
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
	// set flow - power & angle
	void setFlow(sf::Vector2f flow);
private:
	// flow power
	sf::Vector2f m_flowPower;
	// init
	void init();
	static const int ANIM_FREQUENCY = 100;
};

