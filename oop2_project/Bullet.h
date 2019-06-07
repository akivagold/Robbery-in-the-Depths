#pragma once
//---- include section ------
#include <string>
#include "Projectile.h"
#include "AK47.h"
#include "Tool.h"

//---- using section --------
using std::string;

/*
 * Bullet class
 */
class Bullet :
	public Projectile
{
public:
	// constructor
	explicit Bullet(GameScreen& gameScreen, Character* owner, Direction Direction);
	// convert to string
	virtual string toString() const override { return "Bullet { " + Projectile::toString() + " }"; }
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
	virtual void onCollide(MachineGun* machineGun) override {}; // TODO use this
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
	// event when direction changed
	virtual void onDirectionChanged() override { }
private:
	// bullet acceleration
	static const sf::Vector2f ACCELERATION;
	// damage
	static const int DAMAGE = 1;
	// init
	void init();
};

