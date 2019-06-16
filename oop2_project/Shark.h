#pragma once
//---- include section ------
#include <string>
#include "NPC.h"

//---- using section --------
using std::string;

/*
 * Shark class
 */
class Shark
	: public NPC
{
public:
	// constructor
	explicit Shark(GameScreen& gameScreen, int numOfLife = DEFAULT_LIFE);
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
	virtual void onCollide(Flow* flow) override;
	virtual void onCollide(Bullet* bullet) override;
	virtual void onCollide(MachineGun* machineGun) override {}
	virtual void onCollide(Grenade* grenade) override;
	virtual void onCollide(Explosion* explosion) override;
	virtual void onCollide(Box* box) override {}
	virtual void onCollide(ExitLevel* exitLevel) override {}
	// convert to string
	virtual string toString() const override { return "Shark: { " + NPC::toString() + " }"; }
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
	// event when direction changed
	virtual void onDirectionChanged() override;
	// event on die
	virtual void onDie() override;
private:
	// char
	static const char CHAR = 's';
	// draw priority
	static const int DRAW_PRIORITY = 70;
	// default number of life
	static const int DEFAULT_LIFE = 3;
	// damage
	static const int DAMAGE = 2;
	// register flag in BOFactory
	static bool isRegistered;
	// radius attak
	static const float RADIUS_ATTACK;
	// get shark size
	static const sf::Vector2i& getSharkSize();
	// thinking time
	Timer m_thinkingTime;
	// flag that check if he is in thinking state
	bool m_isInThinking;
	// flag that check if he is in radius from player
	bool m_isInRadiusFromPlayer;
	// play when inside radius from player
	void inRadiusFromPlayer();
	// init
	void init();
};


