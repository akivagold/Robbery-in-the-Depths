#pragma once

//---- include section ------
#include <string>
#include "NPC.h"
#include "MovingObject.h"
#include "AK47.h"
#include "Timer.h"

//---- using section --------
using std::string;

/*
 * MachineGun class
 */
class MachineGun :
	public NPC
{
public:
	// char
	static const char CHAR = 'g';
	// constructor
	explicit MachineGun(GameScreen& gameScreen, MovingObject::Direction directoin);
	// convert to string
	virtual string toString() const override { return "MachineGun: { " + InteractableObject::toString() + " }"; }
	// get gun
	const std::shared_ptr<HotWeapon>& getGun() const { return m_gun; }
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const override { return false; }
	// draw
	virtual void draw() override;
	// set weapon
	void setWeapon(const std::shared_ptr<HotWeapon>& weapon) { m_gun = weapon; }
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) override {}
	virtual void onCollide(Player* player) override {}
	virtual void onCollide(Shark* shark) override {}
	virtual void onCollide(Crab* crab) override {}
	virtual void onCollide(Rubber* rubber) override {}
	virtual void onCollide(Chest* chest) override {}
	virtual void onCollide(Wall* wall) override {}
	virtual void onCollide(Flow* flow) override {}
	virtual void onCollide(Bullet* bullet) override {}
	virtual void onCollide(MachineGun* machineGun) override {}
	virtual void onCollide(Grenade* grenade) override {} // TODO use this
	virtual void onCollide(Explosion* explosion) override {}  // TODO use this
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override {};
	// event when direction changed
	virtual void onDirectionChanged() override { }
private:
	// draw priority
	static const int DRAW_PRIORITY = 7;
	// default number of life
	static const int DEFAULT_LIFE = INT_MAX;
	// radius shot
	static const float RADIUS_SHOT;
	// gun
	std::shared_ptr<HotWeapon> m_gun;
	// timer
	Timer m_time;
	// init
	void init();
};

