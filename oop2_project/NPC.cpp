#include "NPC.h"

NPC::NPC(GameScreen& gameScreen, int numOfLife)
	: Character(gameScreen, numOfLife)
{ }

MovingObject::Direction NPC::getRandomUPDirections()
{
	int num = rand() % 3;
	Direction direct;
	if (num == 2)
		direct = Direction::UP_LEFT;
	else
		direct = static_cast<Direction>(num);
	return direct;
}

MovingObject::Direction NPC::getRandomRightDirections()
{
	int num = (rand() % 3) + 1;
	Direction direct = static_cast<Direction>(num);
	return direct;
}

MovingObject::Direction NPC::getRandomDownDirections() 
{
	int num = (rand() % 3) + 3;
	Direction direct = static_cast<Direction>(num);
	return direct;
}

MovingObject::Direction NPC::getRandomLeftDirections() 
{
	int num = (rand() % 3) + 5;
	Direction direct = static_cast<Direction>(num);
	return direct;
}

bool NPC::isUpDirections(Direction direct)
{
	return ((direct == Direction::UP || direct == Direction::UP_LEFT) || direct == Direction::UP_RIGHT);
}

bool NPC::isRightDirections(Direction direct) 
{
	return(direct == Direction::RIGHT || direct == Direction::DOWN_RIGHT || direct == Direction::UP_RIGHT);;
}

bool NPC::isDownDirections(Direction direct)
{
	return (direct == Direction::DOWN || direct == Direction::DOWN_LEFT || direct == Direction::DOWN_RIGHT);
}

bool NPC::isLeftDirections(Direction direct)
{
	return (direct == Direction::LEFT || direct == Direction::DOWN_LEFT || direct == Direction::UP_LEFT);
}
