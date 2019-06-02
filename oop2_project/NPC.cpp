#include "NPC.h"
#include "GameScreen.h"

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

float NPC::getRadiusFromPlayer() const
{
	return getDistance(getGameScreen().getWorld().getBODS().getPlayer());
}
