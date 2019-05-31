#include "Flow.h"
#include "MovingObject.h"

Flow::Flow(GameScreen& gameScreen)
	: StaticObject(gameScreen)
{
	init();
}

void Flow::init()
{
	setAnimation("sea_star");
}

void Flow::onCollide(MovingObject* obj)
{
	obj->setExternaAlcceleration(m_flowPower);
}

