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
	enum Direction { UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT, STANDING };
	// number of directions
	static const int NUM_OF_DIRECTIONS = 8;
	// convert to string
	virtual string toString() const override { return "MovingObject: { " + InteractableObject::toString() + " }"; } // TODO print speed,acc etc.
	// draw
	virtual void draw() override;
	// set direction
	void setDirection(Direction direct);
	// get direction
	Direction getDirection() const { return m_direction; }
	// get last direction
	Direction getLastDirection() const { return m_lastDirection; }
	// get ranodm direction
	static Direction getRandomDirect();
	// get ranodm direction
	static Direction getRandomLeftRightDirect();
	// event when direction changed
	virtual void onDirectionChanged() = 0;
	// suicide
	void suicide();
	// get speed (const access)
	const sf::Vector2f& getSpeed() const { return m_speed; }
	// get interalAcceleration (const access)
	const sf::Vector2f& getInteralAcceleration() const { return m_interalAcceleration; }	
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const override { return true; }
	// set external acceleration
	void setExternaAlcceleration(sf::Vector2f acceleration);
	// get default size of moving object
	static const sf::Vector2i& getMODefSize();
protected:
	// constructor
	explicit MovingObject(GameScreen& gameScreen);
	// get speed (can change)
	sf::Vector2f& getSpeed() { return m_speed; }
	// get interalAcceleration (can change)
	sf::Vector2f& getInteralAcceleration() { return m_interalAcceleration; }
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) = 0;
	// get friction
	sf::Vector2f getFriction() const;
	// set maximum speed
	void setMaxSpeed(const sf::Vector2f& maxSpeed) { m_maxSpeed = maxSpeed; }
	// get maximum speed
	const sf::Vector2f& getMaxSpeed() const { return m_maxSpeed; }
	virtual void floatEffect();
private:
	// direction and last direction
	Direction m_direction, m_lastDirection;
	// flag that check if collide last time
	bool m_isCollided;
	// time clock & float effect clock
	sf::Clock m_clock, m_floatEffectClock;
	sf::Vector2f m_floatAcc;
	sf::Int32 m_lastFloatEffectClock;
	// last float direction
	bool upLastFloatEffect;
	// speed, internal and external acceleration
	sf::Vector2f m_maxSpeed, m_speed, m_interalAcceleration, m_externalAcc;
	// max speed default
	static const sf::Vector2f MAX_SPEED_DEFAULT;
	// if can move to new position
	bool canMove(std::forward_list<BoardObject*> collideList) const;
	// return where the object is trying to move
	sf::Vector2f getNextPosition();
	// play
	void play();
	// init
	void init();
	// check collide
	void checkCollide(std::forward_list<BoardObject*> collideList);
};
