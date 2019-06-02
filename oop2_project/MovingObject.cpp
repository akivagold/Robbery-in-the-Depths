#include "MovingObject.h"
#include "GameScreen.h"


sf::Vector2f MovingObject::getFriction() const
{
	sf::Vector2f friction;
	//TODO add external acc(?)

	friction.x = m_speed.x / (m_maxSpeed.x);// + m_externalMaxSpeed.x);
	friction.y = m_speed.y / (m_maxSpeed.y);// + m_externalMaxSpeed.y);
	return friction;
}

void MovingObject::setExternaAlcceleration(sf::Vector2f acceleration)
{
	// need m_externalMaxSpeed?
	m_externalAcc.x = acceleration.x;
	m_externalAcc.y = acceleration.y;
}

void MovingObject::checkCollide(std::forward_list<BoardObject*> collideList)
{
	setExternaAlcceleration(sf::Vector2f(0.f, 0.f));
	// check all list
	for (auto& object : collideList) {
		object->onCollide(this);
	}
}

const sf::Vector2i& MovingObject::getMODefSize()
{
	static const sf::Vector2i MOVING_OBJ_SIZE(static_cast<int>(0.8f*float(getDefaultSize().x)), 
		static_cast<int>(0.8f*float(getDefaultSize().y)));
	return MOVING_OBJ_SIZE;
}

MovingObject::MovingObject(GameScreen& gameScreen)
	: InteractableObject(gameScreen), m_maxSpeed(sf::Vector2f(500, 500)), 
	  m_isCollided(false), m_direction(STANDING), m_lastDirection(STANDING)	//TODO enum
{
	init();
}

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
		// check collision effect
		checkCollide(collideList);
	}
}

void MovingObject::init()
{
	m_externalAcc.x = m_speed.x = m_interalAcceleration.x = 0;
	m_externalAcc.y = m_speed.y = m_interalAcceleration.y = 0;

	setSize(getMODefSize());
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
	m_speed.x += (m_interalAcceleration.x + m_externalAcc.x - friction.x) * elapsedTime; // TODO external acc
	m_speed.y += (m_interalAcceleration.y + m_externalAcc.y - friction.y) * elapsedTime;
	float x_pos = getPosition().x + m_speed.x * elapsedTime;
	float y_pos = getPosition().y + m_speed.y * elapsedTime;
	return sf::Vector2f(x_pos, y_pos);
}

MovingObject::Direction MovingObject::getRandomDirect()
{
	int num = rand() % NUM_OF_DIRECTIONS;
	Direction direct = static_cast<Direction>(num);
	return direct;
}

MovingObject::Direction MovingObject::getRandomLeftRightDirect()
{
	return (rand() % 2) ? Direction::LEFT : Direction::RIGHT;	
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

