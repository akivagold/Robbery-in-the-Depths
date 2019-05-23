#pragma once
//---- include section ------
#include <string>
#include "BaseScreen.h"
#include "RelativeLayout.h"

//---- using section --------
using std::string;

/*
 * GameScreen class
 */
class GameScreen
	: public GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>
{}
	/*
public:
	// constructor
	GameScreen();
	// convert to string
	virtual string toString() const; // overide;
private:

};*/


