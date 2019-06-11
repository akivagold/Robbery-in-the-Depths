#include "Wall.h"
#include "BOFactory.h"

// register
bool Wall::isRegistered = BOFactory::getInterface().registerIn(Wall::CHAR, [](GameScreen& gameScreen) { return std::make_unique<Wall>(gameScreen); });

Wall::Wall(GameScreen& gameScreen)
	: UnInteractableObject(gameScreen)
{
	init();
}

string Wall::toString() const
{
	return "Wall: { " + UnInteractableObject::toString() + " }";
}

void Wall::init()
{
	
	setAnimation("wall");
	setDrawPriority(DRAW_PRIORITY);
}
