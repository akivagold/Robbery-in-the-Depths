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
	// direction of moving
	enum Direction { UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT , UP_LEFT, STANDING };
	static const int NUM_OF_DIRECTIONS = 8;
	// convert to string
	virtual string toString() const override { return "MovingObject: {" + InteractableObject::toString() + " }"; } // TODO print speed,acc etc.
	// draw
	virtual void draw() override;
	// return where the object is trying to move
	sf::Vector2f getNextPosition();
	// set direction
	void setDirection(Direction direct) { m_direction = direct; }
	// get direction
	Direction getDirection() const { return m_direction; }
	// get ranodm direction
	Direction getRandomDirect() const;
	// on direction change
	//virtual void onDirectionChange() = 0;
	// suicide
	// TODO void suicide() { getGameScreen().getWorld().getBODS().requestRemoveBO(?); }
	// get speed (const access)
	const sf::Vector2f& getSpeed() const { return m_speed; }
	sf::Vector2f& getSpeed() { return m_speed; }
protected:
	// constructor
	explicit MovingObject(GameScreen& gameScreen);
	// get speed (can change)
	//sf::Vector2f& getSpeed() { return m_speed; }
	// the object choose where to go
	virtual void playChoice() = 0;
	// play
	virtual void play();
private:
	// if can move to new position
	bool canMove(std::forward_list<BoardObject*> collideList) const;
	// speed, internal land external acceleration
	sf::Vector2f m_speed, m_interalAcceleration, m_externalAcc;
	// time
	sf::Clock m_clock;
	// get collides list
	std::forward_list<BoardObject*> getCollidesList();
	// direction
	Direction m_direction;
};

