#pragma once
//---- include section ------
#include <string>
#include "InteractableObject.h"
#include <forward_list> 

//---- using section --------
using std::string;

/*
 * MovingObject class
 */
class MovingObject
	: public InteractableObject
{
public:
	// constructor
	explicit MovingObject(sf::RenderWindow& window, GameScreen& gameScreen);
	// play
	virtual void play();
	// convert to string
	virtual string toString() const override { return "MovingObject: {" + InteractableObject::toString() + " }"; }
	// return where the object is trying to move
	sf::Vector2f getNextPosition();
protected:
	// the object choose where to go
	virtual void playChoice() = 0;
private:
	bool canMove(std::forward_list<BoardObject*> collideList);
	sf::Vector2f m_speed, m_interalAcceleration, m_externalAcc;
	sf::Clock m_clock;
};

