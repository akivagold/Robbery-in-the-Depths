#include "Character.h"

Character::Character(sf::RenderWindow& window, GameScreen& gameScreen, int numOfLife)
	: MovingObject(window, gameScreen)
{
	setLife(numOfLife);
}

void Character::setLife(int numOfLife) const
{
	if (numOfLife < 0)
		throw std::out_of_range("num of life " + std::to_string(numOfLife) + " is illegal");
}

string Character::toString() const
{
	return "Character: { " + MovingObject::toString() + " } ";
}
