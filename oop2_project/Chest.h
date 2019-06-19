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
private:
	// char
	static const char CHAR = 'm';
	// draw priority
	static const int DRAW_PRIORITY = 10;
	// open chest animation time
	static const int OPEN_CHEST_ANIM_TIME = 300;
	// get chest size
	static const sf::Vector2i& getChestSize();
	// register flag in BOFactory
	static bool isRegistered;
	// open chest stopWatch
	StopWatch m_openChestSW;
	// init
	void init();
};

