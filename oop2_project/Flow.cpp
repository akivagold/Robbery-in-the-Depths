#include "Flow.h"
#include "MovingObject.h"

Flow::Flow(GameScreen& gameScreen)
	: StaticObject(gameScreen)
{
	init();
}

void Flow::init()
{
	setAnimation("flow");
	setAnimationFrequency(ANIM_FREQUENCY);
}

