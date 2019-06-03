#include "Character.h"

Character::Character(GameScreen& gameScreen, int numOfLife)
	: MovingObject(gameScreen), m_isDie(false)
{
	setNumOfLife(numOfLife);
}

void Character::playChoice(Direction lastDirection, bool isCollided)
{
	if (isDie()) {
		getInteralAcceleration().x = 0.f;
		getInteralAcceleration().y = 0.000005f*getMODefSize().y;
	}
}

void Character::setNumOfLife(int numOfLife)
{
	if (numOfLife < 0)
		throw std::out_of_range("num of life " + std::to_string(numOfLife) + " is illegal");
	if (isDie())
		throw std::logic_error("The " + toString() + " already die. only god able to resurrection");
	m_numOfLife = numOfLife;
	if (numOfLife == 0) {
		m_isDie = true;
		onDie();
	}
}

bool Character::isUpDirections(Direction direct)
{
	return ((direct == Direction::UP || direct == Direction::UP_LEFT) || direct == Direction::UP_RIGHT);
}

bool Character::isRightDirections(Direction direct)
{
	return(direct == Direction::RIGHT || direct == Direction::DOWN_RIGHT || direct == Direction::UP_RIGHT);;
}

bool Character::isDownDirections(Direction direct)
{
	return (direct == Direction::DOWN || direct == Direction::DOWN_LEFT || direct == Direction::DOWN_RIGHT);
}

bool Character::isLeftDirections(Direction direct)
{
	return (direct == Direction::LEFT || direct == Direction::DOWN_LEFT || direct == Direction::UP_LEFT);
}

void Character::draw()
{
	MovingObject::draw();
	m_vanishSW.checkStopWatch();
}

void Character::onDie()
{
	m_vanishSW.start(DIE_VANISH_TIME, [this] {
		suicide();
	});
}

string Character::toString() const
{
	return "Character: { numOfLife=" + std::to_string(m_numOfLife) + ", " + MovingObject::toString() + " }";
}
