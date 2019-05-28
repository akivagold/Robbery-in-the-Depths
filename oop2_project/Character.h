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
	bool hasNoLife() const { return (m_numOfLife == 0); }
	// convert to string
	virtual string toString() const override;
protected:
	// constructor
	explicit Character(GameScreen& gameScreen, int numOfLife = 0);
private:
	// number of life
	int m_numOfLife;
};


