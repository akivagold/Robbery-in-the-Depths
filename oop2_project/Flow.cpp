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
	obj->setExternalSpeed(sf::Vector2f(100.f, 100.f), sf::Vector2f(0.0025f, 0.0025f));
}

