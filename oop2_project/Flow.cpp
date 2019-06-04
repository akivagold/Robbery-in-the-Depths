#include "Flow.h"
#include "MovingObject.h"

Flow::Flow(GameScreen& gameScreen)
	: StaticObject(gameScreen)
{
	init();
}

void Flow::setFlow(sf::Vector2f flow)
{
	m_flowPower = flow;
	rotateAnimation(std::atan2(-flow.x , -flow.y) * 180 / M_PI);
}

void Flow::init()
{
	setAnimation("flow");
	setAnimationFrequency(ANIM_FREQUENCY);
}

