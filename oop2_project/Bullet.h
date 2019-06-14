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
	explicit Bullet(GameScreen& gameScreen, Character* owner);
	// explode
	virtual void explode() override;
	// draw
	virtual void draw() override;
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
	virtual void onCollide(Box* box) override;
	virtual void onCollide(ExitLevel* exitLevel) override {}
	// convert to string
	virtual string toString() const override { return "Bullet: { " + Projectile::toString() + " }"; }
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
	// event when direction changed
	virtual void onDirectionChanged() override { }
	// event when object joined to game
	virtual void onJoinedGame() override;
private:
	// bullet acceleration
	static const sf::Vector2f ACCELERATION;
	// time
	Timer m_time;
	// damage
	static const int DAMAGE = 1;
	// init
	void init();
};

