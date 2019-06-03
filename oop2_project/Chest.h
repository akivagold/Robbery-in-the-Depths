#pragma once
//---- include section ------
#include "Container.h"
#include "Surprise.h"
#include <string>
#include "StopWatch.h"

//---- using section --------
using std::string;

/*
 * Chest class
 */
class Chest :
	public Container
{
public:
	// char
	static const char CHAR = 'm';
	// constructor
	explicit Chest(GameScreen& gameScreen);
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const override { return true; }
	// pickup
	virtual void pickup(Player* owner) override;
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override;
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) override { obj->onCollide(this); }
	virtual void onCollide(Player* player) override {} // TODO use this
	virtual void onCollide(Shark* shark) override {} // TODO use this
	virtual void onCollide(Crab* crab) override {} // TODO use this
	virtual void onCollide(Cop* cop) override {} // TODO use this
	virtual void onCollide(Chest* chest) override {} // TODO use this
	virtual void onCollide(Wall* wall) override {} // TODO use this
	virtual void onCollide(Flow* flow) override {} // TODO use this
	virtual void onCollide(Bullet* bullet) override {} // TODO use this
private:
	// draw priority
	static const int DRAW_PRIORITY = 10;
	// open chest animation time
	static const int OPEN_CHEST_ANIM_TIME = 300;
	// init
	void init();
	// open chest stopWatch
	StopWatch m_openChestSW;
};

