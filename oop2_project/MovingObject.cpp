#include "MovingObject.h"
#include "GameScreen.h"


sf::Vector2f MovingObject::getFriction()
{
	sf::Vector2f friction;
	//TODO add external acc(?)

	friction.x = m_speed.x / m_maxSpeed.x;
	friction.y = m_speed.y / m_maxSpeed.y;
	return friction;
}

MovingObject::MovingObject(GameScreen& gameScreen)
	: InteractableObject(gameScreen), m_maxSpeed(sf::Vector2f(500, 500)), 
	  m_isCollided(false), m_direction(STANDING), m_lastDirection(STANDING)	//TODO enum
{}

void MovingObject::play()
{
	// choose where to go
	playChoice(m_lastDirection, m_isCollided);

	// save previous location
	sf::Vector2f prePos = getPosition();

	// get next position
	sf::Vector2f nextPos = getNextPosition();

	if (nextPos != prePos) {
		// move to next position
		setPosition(nextPos);

		std::forward_list<BoardObject*> collideList = getCollidesList();
		// check if can move to new position
		if (!canMove(collideList)) {
			m_isCollided = true;
			setPosition(prePos);
			m_speed = sf::Vector2f(0, 0);
		}
		else {
			m_isCollided = false;
		}
	}
}

void MovingObject::draw()
{
	InteractableObject::draw();
	play();
}

void MovingObject::setDirection(Direction direct)
{
	if (direct != m_direction) {
		m_lastDirection = m_direction;
		m_direction = direct;
		onDirectionChanged();
	}
}

sf::Vector2f MovingObject::getNextPosition()
{
	sf::Vector2f friction = getFriction();
	sf::Int32 elapsedTime = m_clock.getElapsedTime().asMilliseconds();
	m_clock.restart();
	m_speed.x += (m_interalAcceleration.x - friction.x) * elapsedTime; // TODO external acc
	m_speed.y += (m_interalAcceleration.y - friction.y) * elapsedTime;
	float x_pos = getPosition().x + m_speed.x * elapsedTime;
	float y_pos = getPosition().y + m_speed.y * elapsedTime;
	return sf::Vector2f(x_pos, y_pos);
}

MovingObject::Direction MovingObject::getRandomDirect() const
{
	int num = rand() % NUM_OF_DIRECTIONS;
	Direction direct = static_cast<Direction>(num);
	return direct;
}

void MovingObject::suicide()
{
	getGameScreen().getWorld().getBODS().requestRemoveBO(getSelf());
}

bool MovingObject::canMove(std::forward_list<BoardObject*> collideList) const
{
	if ((getPosition().x < 0 || getPosition().x + getSize().x > getGameScreen().getWorld().getSize().x) ||
		((getPosition().y < 0 || getPosition().y + getSize().y > getGameScreen().getWorld().getSize().y)))
		return false;
	// check all list
	for (auto object : collideList) {
		// if can't go through at least one return false
		if (!object->canMoveThroughMe()) {
			return false;
		}
	}
	return true;
}

