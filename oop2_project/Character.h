#pragma once
//---- include section ------
#include <string>
#include "MovingObject.h"

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
	// get number of life
	int getNumOfLife() const { return m_numOfLife; }
	// check if has no life
	bool isDie() const { return (m_numOfLife == 0); }
	// event on die
	// TODO virtual void onDie() = 0;
	// convert to string
	virtual string toString() const override;
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
private:
	// number of life
	int m_numOfLife;
};


