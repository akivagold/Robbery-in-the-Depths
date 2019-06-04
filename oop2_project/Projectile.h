#pragma once
//---- include section ------
#include <string>
#include "MovingObject.h"
#include "Character.h"

//---- using section --------
using std::string;

/*
 * Projectile class
 */
class Projectile :
	public MovingObject
{
public:
	// constructor
	explicit Projectile(GameScreen& gameScreen, Character* owner,  Direction direction = Direction::RIGHT);
	// convert to string
	virtual string toString() const override { return "Projectile { " + MovingObject::toString() + " }"; }
	// get my owner
	Character* getMyOwner() { return m_owner; }
protected:
	// draw priority
	static const int DRAW_PRIORITY = 22;
	// init
	void init(Direction direction);
	// my owner
	Character* m_owner;

};

