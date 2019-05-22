#pragma once
//---- include section ------
#include <string>

//---- using section --------
using std::string;

/*
 * $$$$$$$$$ExampleClass$$$$$$$$$$$ class
 */
class ExampleClass
{
public:
	// constructor
	ExampleClass();
	// convert to string
	virtual string toString() const; // overide;
private:

};

