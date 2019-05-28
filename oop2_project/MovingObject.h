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
	// convert to string
	virtual string toString() const override { return "MovingObject: {" + InteractableObject::toString() + " }"; } // TODO print speed,acc etc.
	// draw
	virtual void draw() override;
	// return where the object is trying to move
	sf::Vector2f getNextPosition();
	// suicide
	// TODO void suicide() { getGameScreen().getWorld().getBODS().requestRemoveBO(?); }
	// get speed (const access)
	const sf::Vector2f& getSpeed() const { return m_speed; }
protected:
	// constructor
	explicit MovingObject(GameScreen& gameScreen);
	// get speed (can change)
	sf::Vector2f& getSpeed() { return m_speed; }
	// the object choose where to go
	virtual void playChoice() = 0;
	// play
	virtual void play();
private:
	bool canMove(std::forward_list<BoardObject*> collideList) const;
	sf::Vector2f m_speed, m_interalAcceleration, m_externalAcc;
	sf::Clock m_clock;
};

