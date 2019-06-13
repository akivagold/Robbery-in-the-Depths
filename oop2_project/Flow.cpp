#include "Flow.h"
#include "MovingObject.h"

Flow::Flow(GameScreen& gameScreen)
	: StaticObject(gameScreen)
{
	init();
}

void Flow::setFlow(const sf::Vector2f& flow)
{
	m_flowPower = flow;
	// TODO fix this:    rotateAnimation(float(std::atan2(-flow.x , -flow.y) * 180.f / M_PI));
	// or this:		rotateViewAt(getWindow().mapPixelToCoords(sf::Vector2i(getSprite().getPosition())), getSprite(), std::atan2(flow.x, -flow.y) * 180.f / M_PI);
	
}

void Flow::init()
{
	setDrawPriority(DRAW_PRIORITY);
	setAnimation("flow");
	setAnimationFrequency(ANIM_FREQUENCY);
}

