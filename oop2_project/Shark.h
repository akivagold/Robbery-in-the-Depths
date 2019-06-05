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
	// char
	static const char CHAR = 's';
	// constructor
	explicit Shark(GameScreen& gameScreen, int numOfLife = DEFAULT_LIFE);
	// event when direction changed
	virtual void onDirectionChanged() override;
	// event on die
	virtual void onDie() override;
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override { return "Shark: { " + NPC::toString() + " }"; }
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) override { obj->onCollide(this); }
	virtual void onCollide(Player* player) override {} // TODO use this
	virtual void onCollide(Shark* shark) override {} // TODO use this
	virtual void onCollide(Crab* crab) override {} // TODO use this
	virtual void onCollide(Rubber* rubber) override {} // TODO use this
	virtual void onCollide(Chest* chest) override {} // TODO use this
	virtual void onCollide(Wall* wall) override {} // TODO use this
	virtual void onCollide(Flow* flow) override;
	virtual void onCollide(Bullet* bullet) override;
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
private:
	// draw priority
	static const int DRAW_PRIORITY = 70;
	// default number of life
	static const int DEFAULT_LIFE = 3;
	// radius attack
	float m_radiusAttack;
	// timer
	Timer m_time;
	// flag that check if shark in chase
	bool m_inChase;
	// init
	void init();
	// get shark size
	static const sf::Vector2i& getSharkSize();	
};


