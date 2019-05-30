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
	// constructor
	Surprise() = default;
	// convert to string
	virtual string toString() const { return "Surprise: { }"; }
};

