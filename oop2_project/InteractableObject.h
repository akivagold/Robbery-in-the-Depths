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
	// get damage
	int getDamage() const { return m_damage; }
	// convert to string
	virtual string toString() const override { return "InteractableObject: { " + BoardObject::toString() + ", damage=" + std::to_string(m_damage) + " }"; }
protected:
	// constructor
	explicit InteractableObject(GameScreen& gameScreen);
	// set damage
	void setDamage(int damage) { m_damage = damage; }
private:
	// object damge
	int m_damage;
};

