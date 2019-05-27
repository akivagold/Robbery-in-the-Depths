#pragma once
//---- include section ------
#include <string>
#include "BoardObject.h"

//---- using section --------
using std::string;

/*
 * InteractableObject class
 */
class InteractableObject
	: public BoardObject
{
public:
	// constructor
	explicit InteractableObject(sf::RenderWindow& window, GameScreen& gameScreen);
	// convert to string
	virtual string toString() const override { return "InteractableObject: {" + BoardObject::toString() + "}"; }
protected:
	// set damge
	void setDamage(int damage) { m_damage = damage; }
private:
	// object damge
	int m_damage;
};

