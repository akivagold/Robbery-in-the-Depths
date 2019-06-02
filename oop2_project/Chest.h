#pragma once
//---- include section ------
#include "Container.h"
#include "Surprise.h"
#include <string>

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
	// TODO virtual void pickup(std::shared_ptr<Player>& owner) override;
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
	// init
	void init();
};

