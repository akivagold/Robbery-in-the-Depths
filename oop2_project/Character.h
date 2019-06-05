#pragma once
//---- include section ------
#include <string>
#include "MovingObject.h"
#include "StopWatch.h"
class Tool;

//---- using section --------
using std::string;

/*
 * Character class
 */
class Character
	: public MovingObject
{
public:
	// set life
	virtual void setNumOfLife(int numOfLife);
	// decrease life
	void decreaseLife(int numOfLife);
	// get number of life
	int getNumOfLife() const { return m_numOfLife; }
	// check if has no life
	bool isDie() const { return m_isDie; }
	// draw
	virtual void draw() override;
	// event on die
	virtual void onDie();
	// die (vanish after some time)
	void die() { setNumOfLife(0); }
	// convert to string
	virtual string toString() const override;
	// event on update tool
	virtual void onToolUpdated(Tool* tool) {}
	// check if is up directions
	static bool isUpDirections(Direction direct);
	// check if is right directions
	static bool isRightDirections(Direction direct);
	// check if is down directions
	static bool isDownDirections(Direction direct);
	// check if is left directions
	static bool isLeftDirections(Direction direct);
protected:
	// constructor
	explicit Character(GameScreen& gameScreen, int numOfLife = 0);
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
private:
	// time before vanish when die
	static const int DIE_VANISH_TIME = 5000;
	// number of life
	int m_numOfLife;
	// die flag
	bool m_isDie;
	// vanish stopWatch
	StopWatch m_vanishSW;
	// disable using suicide. use die instead
	using MovingObject::suicide;
};


