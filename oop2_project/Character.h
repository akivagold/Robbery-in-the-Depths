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
	// constructor
	Character(sf::RenderWindow& window, GameScreen& gameScreen, int numOfLife = 0);
	// set life
	virtual void setLife(int numOfLife) const;
	// convert to string
	virtual string toString() const override;
private:
	int m_numOfLife;
};


