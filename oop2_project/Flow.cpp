#include "Flow.h"
#include "MovingObject.h"

Flow::Flow(GameScreen& gameScreen)
	: StaticObject(gameScreen)
{ }

void Flow::init()
{
	setAnimation("coin");
}

void Flow::onCollide(const std::shared_ptr<MovingObject>& obj)
{
	obj->setExternalSpeed(sf::Vector2f(100.f, 100.f), sf::Vector2f(0.0025f, 0.0025f));
}

