#pragma once
//---- include section ------
#include <string>
#include "Projectile.h"

//---- using section --------
using std::string;

/*
 * Bullet class
 */
class Bullet :
	public Projectile
{
public:
	// constructor
	explicit Bullet(GameScreen& gameScreen, Direction Direction);
	// convert to string
	virtual string toString() const override { return "Bullet { " + Projectile::toString() + " }"; }
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
	// event when direction changed
	virtual void onDirectionChanged() override {}; // TODO
private:
	// init
	void init();
};

