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

void NPC::setDirectionAfterCollid(Direction direction)
{
	if (isUpDirections(direction))
		setDirection(getRandomDownDirections());
	else if (isDownDirections(direction))
		setDirection(getRandomUPDirections());
	else if (isRightDirections(direction))
		setDirection(getRandomLeftDirections());
	else
		setDirection(getRandomRightDirections());
}

void NPC::goByDirection(Direction direction)
{
	float offset = 0.00025f;
	switch (direction)
	{
		case Direction::UP: {
			getInteralAcceleration().y = -offset;
		} break;
		case Direction::UP_RIGHT: {
			getInteralAcceleration().y = -offset;
			getInteralAcceleration().x = offset;
		} break;
		case Direction::RIGHT: {
			getInteralAcceleration().x = offset;
		} break;
		case Direction::DOWN_RIGHT: {
			getInteralAcceleration().y = offset;
			getInteralAcceleration().x = offset;
		} break;
		case Direction::DOWN: {
			getInteralAcceleration().y = offset;
		} break;
		case Direction::DOWN_LEFT: {
			getInteralAcceleration().y = offset;
			getInteralAcceleration().x = -offset;
		} break;
		case Direction::LEFT: {
			getInteralAcceleration().y = offset;
		} break;
		case Direction::UP_LEFT: {
			getInteralAcceleration().y = -offset;
			getInteralAcceleration().x = -offset;
		} break;
	}
}

float NPC::getRadiusFromPlayer() const
{
	return getDistance(getGameScreen().getWorld().getBODS().getPlayer());
}
