#pragma once
//---- include section ------
#include <string>
#include "MovingObject.h"

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
	explicit Projectile(GameScreen& gameScreen, Direction direction = Direction::RIGHT);
	// convert to string
	virtual string toString() const override { return "Projectile { " + MovingObject::toString() + " }"; }
protected:
	// draw priority
	static const int DRAW_PRIORITY = 22;
	// init
	void init(Direction direction);

};

