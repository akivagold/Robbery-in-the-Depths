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

string Character::toString() const
{
	return "Character: { " + MovingObject::toString() + " } ";
}
