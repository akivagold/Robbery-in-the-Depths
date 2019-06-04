#pragma once
//---- include section ------
#include <string>
#include "Surprise.h"

//---- using section --------
using std::string;

/*
 * Gift class
 */
class Gift :
	public Surprise
{
public:
	// convert to string
	virtual string toString() const override { return "Gift: { " + Surprise::toString() + " }"; }
protected:
	// constructor
	Gift() = default;
};

