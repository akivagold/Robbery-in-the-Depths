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
	// pickup content
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
	static const int DRAW_PRIORITY = 10;
	// open chest animation time
	static const int OPEN_CHEST_ANIM_TIME = 300;
	// open chest stopWatch
	StopWatch m_openChestSW;
	// init
	void init();
	// get chest size
	static const sf::Vector2i& getChestSize();
	// register flag in BOFactory
	static bool isRegistered;
};

