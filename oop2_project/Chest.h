#pragma once
//---- include section ------
#include "Container.h"
#include "Surprise.h"
#include <string>

//---- using section --------
using std::string;

/*
 * Chest class
 */
class Chest :
	public Container
{
public:
	// constructor
	explicit Chest(GameScreen& gameScreen);
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const override { return true; }
	// convert to string
	virtual string toString() const override;
private:
	// draw priority
	static const int DRAW_PRIORITY = 10;
	// init
	void init();
};
