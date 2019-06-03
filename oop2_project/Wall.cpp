#include "Wall.h"

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
