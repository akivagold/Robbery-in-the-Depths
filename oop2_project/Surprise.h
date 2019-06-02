#pragma once
//---- include section ------
#include <string>

//---- using section --------
using std::string;

/*
 * Surprise class
 */
class Surprise
{
public:
	// convert to string
	virtual string toString() const { return "Surprise: { }"; }
protected:
	// constructor
	Surprise() = default;
};

