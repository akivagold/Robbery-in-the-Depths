#pragma once
//---- include section ------
#include <string>
class Player;

//---- using section --------
using std::string;

/*
 * Surprise class
 */
class Surprise
{
public:
	// take surprise
	virtual void takeSurprise(Player* owner) = 0;
	// convert to string
	virtual string toString() const { return "Surprise: { }"; }
protected:
	// constructor
	Surprise() = default;
};

