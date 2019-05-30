#include "Crab.h"

Crab::Crab(GameScreen& gameScreen, int numOfLife)
	: NPC(gameScreen, numOfLife), m_isPlayerInRadius(false)
{
	init();
}

void Crab::draw()
{
	NPC::draw();
	m_timer.checkTimer();
}

void Crab::playChoice(Direction lastDirection, bool isCollided)
{
	// check is collided
	if (isCollided) {
		Direction newDirection = (lastDirection == Direction::RIGHT) ? Direction::LEFT : Direction::RIGHT;
		setDirection(newDirection);
	}

	// check if user in my radius

	// set speed
	if (getDirection() == Direction::RIGHT) {
		getInteralAcceleration().x = 0.0002f;
	}
	else {
		getInteralAcceleration().x = -0.0002f;
	}	
}

void Crab::init()
{
	setAnimation("walking_crab");
	setAnimationFrequency(30);
	setDrawPriority(DRAW_PRIORITY);
	int changeDirectionTime = 2000 + rand() % 4000;
	m_timer.start(changeDirectionTime, [this]() {
		Direction direction = getRandomLeftRightDirect();
		setDirection(direction);
		getInteralAcceleration().x = 0;
	});
}