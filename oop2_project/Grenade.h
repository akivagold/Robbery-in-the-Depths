#pragma once
//---- include section ------
#include <string>
#include "Projectile.h"
#include "AK47.h"
#include "Tool.h"

//---- using section --------
using std::string;

/*
 * Grenade class
 */
class Grenade :
	public Projectile
{
public:
	// constructor
	explicit Grenade(GameScreen& gameScreen, Character* owner, float upAmplitude = 0.4f, Direction Direction = Direction::RIGHT);
	// event when object joined to game
	virtual void onJoinedGame() override;
	// explode
	virtual void explode() override;
	// convert to string
	virtual string toString() const override { return "Grenade: { " + Projectile::toString() + " }"; }
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
	virtual void onCollide(Grenade* grenade) override {}; // TODO use this
	virtual void onCollide(Explosion* explosion) override {}  // TODO use this
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
	// event when direction changed
	virtual void onDirectionChanged() override { }
private:
	// acceleration
	static const sf::Vector2f ACCELERATION;
	// damage
	static const int DAMAGE = 5;
	// init
	void init();
	// update acceleration
	void updateAcc();
};

