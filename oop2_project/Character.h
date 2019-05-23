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
{
public:
	// constructor
	Character();
	// convert to string
	// TODO
	//virtual string toString() const override;
	virtual void setLife(int life) { m_life = life; }
private:
	int m_life;
};


