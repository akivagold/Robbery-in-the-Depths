#pragma once
#include "HotWeapon.h"
#include "GameScreen.h"
#include "Bullet.h"

//---- using section --------
using std::string;

/*
 * HotWeapon class
 */
class AK47 :
	public HotWeapon
{
public:
	// constructor
	AK47(std::shared_ptr<MovingObject>& object);
	// convert to string
	virtual string toString() const override;
	// fire
	virtual void fire() override;
private:
	// init
	void init();
};

