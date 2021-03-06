#pragma once
//---- include section ------
#include <string>
#include "NPC.h"
#include "AK47.h"
#include "Tool.h"
#include "Timer.h"

//---- using section --------
using std::string;

/*
 * Rubber class
 */
class Rubber :
	public NPC
{
public:
	// get radius shot
	static float getRadiusShot() { return RADIUS_SHOT; }
	// constructor
	explicit Rubber(GameScreen& gameScreen, int numOfLife = DEFAULT_LIFE);
	// draw
	virtual void draw() override;
	// get gun
	const std::shared_ptr<Tool>& getTool() const { return m_tool; }
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) override { obj->onCollide(this); }
	virtual void onCollide(Player* player) override {}
	virtual void onCollide(Shark* shark) override {}
	virtual void onCollide(Crab* crab) override {}
	virtual void onCollide(Rubber* rubber) override {}
	virtual void onCollide(Chest* chest) override {}
	virtual void onCollide(Wall* wall) override;
	virtual void onCollide(Flow* flow) override;
	virtual void onCollide(Bullet* bullet) override;
	virtual void onCollide(MachineGun* machineGun) override;
	virtual void onCollide(Grenade* grenade) override;
	virtual void onCollide(Explosion* explosion) override;
	virtual void onCollide(Box* box) override;
	virtual void onCollide(ExitLevel* exitLevel) override {}
	// convert to string
	virtual string toString() const override { return "Rubber: { " + NPC::toString() + " }"; }
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
	// event when direction changed
	virtual void onDirectionChanged() override;
	// event on die
	virtual void onDie() override;
private:
	// char
	static const char CHAR = 'r';
	// draw priority
	static const int DRAW_PRIORITY = 80;
	// default number of life
	static const int DEFAULT_LIFE = 3;	
	// radius attak
	static const float RADIUS_ATTACK;
	// radius shot
	static const float RADIUS_SHOT;
	// register flag in BOFactory
	static bool isRegistered;
	// gun
	std::shared_ptr<Tool> m_tool;
	// time
	Timer m_time;
	// recover time
	Timer m_thinkingTime;
	// flag that check if he is in thinking state
	bool m_isInthinking;
	// flag that check if he is in shot state
	bool m_isInShot;
	// flag that check if he is in radius shot
	bool m_isInRadiusShot;
	// flag that check if he is in radius from player
	bool m_isInRadiusfromPlayer;
	// play when inside radius from player
	void inRadiusFromPlayer();
	// init
	void init();
};

