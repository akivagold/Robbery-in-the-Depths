#include "MovingObject.h"
#include "GameScreen.h"

MovingObject::MovingObject(sf::RenderWindow& window, GameScreen& gameScreen)
	: InteractableObject(window, gameScreen)
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
	collideList = getGameScreen().getWorld().getDODS().getAABBTree().queryOverlaps(this);
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
	float x_pos = getPosition().x + m_speed.x * m_clock.getElapsedTime().asMilliseconds();
	float y_pos = getPosition().y + m_speed.y * m_clock.getElapsedTime().asMilliseconds();
	//sf::Vector2f nextPos = getPosition() + (m_speed * m_clock.getElapsedTime().asMilliseconds);
	sf::Vector2f nextPos = sf::Vector2f(x_pos, y_pos);
	m_clock.restart();
	return nextPos;
}

bool MovingObject::canMove(std::forward_list<BoardObject*> collideList)
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

