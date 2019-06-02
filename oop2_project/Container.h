#pragma once
//---- include section ------
#include "StaticObject.h"
#include "Surprise.h"
#include <string>

//---- using section --------
using std::string;

/*
 * Container class
 */
class Container :
	public StaticObject
{
public:
	// get surprises
	const std::vector<std::shared_ptr<Surprise>>& getSurprises() const { return m_surprises; }
	// convert to string
	virtual string toString() const override;
protected:
	// constructor
	explicit Container(GameScreen& gameScreen);
private:
	// surprises
	std::vector<std::shared_ptr<Surprise>> m_surprises;
};

