#include "Character.h"

Character::Character(GameScreen& gameScreen, int numOfLife)
	: MovingObject(gameScreen)
{
	setNumOfLife(numOfLife);
}

void Character::setNumOfLife(int numOfLife)
{
	if (numOfLife < 0)
		throw std::out_of_range("num of life " + std::to_string(numOfLife) + " is illegal");
	m_numOfLife = numOfLife;
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

string Character::toString() const
{
	return "Character: { " + MovingObject::toString() + " } ";
}
