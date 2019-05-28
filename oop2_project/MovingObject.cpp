#include "MovingObject.h"
#include "GameScreen.h"

MovingObject::MovingObject(GameScreen& gameScreen)
	: InteractableObject(gameScreen)
{}

void MovingObject::play()
{
	// choose where to go
	playChoice();

	// save previous location
	sf::Vector2f prePos = getPosition();
	// move to next position
	setPosition(getNextPosition());

	std::forward_list<BoardObject*> collideList;
	collideList = getGameScreen().getWorld().getBODS().getAABBTree().queryOverlaps(this);
	// check if can move to new position
	if (!canMove(collideList)) {
		setPosition(prePos);
	}
}

void MovingObject::draw()
{
	InteractableObject::draw();
	play();
}

sf::Vector2f MovingObject::getNextPosition()
{
	sf::Int32 elapsedTime = m_clock.getElapsedTime().asMilliseconds();
	m_clock.restart();
	float x_pos = getPosition().x + m_speed.x * elapsedTime;
	float y_pos = getPosition().y + m_speed.y * elapsedTime;
	//sf::Vector2f nextPos = getPosition() + (m_speed * m_clock.getElapsedTime().asMilliseconds);
	sf::Vector2f nextPos = sf::Vector2f(x_pos, y_pos);	
	return nextPos;
}

bool MovingObject::canMove(std::forward_list<BoardObject*> collideList) const
{
	// check all list
	for (auto object : collideList) {
		// if can't go through at least one return false
		if (!object->canMoveThroughMe()) {
			return false;
		}
	}
	return true;
}

