#include "Chest.h"

Chest::Chest(GameScreen& gameScreen)
	: Container(gameScreen)
{
	init();
}

string Chest::toString() const
{
	return "Chest: { " + Container::toString() + " }";
}

void Chest::init()
{

	setAnimation("lose"); // TODO
	//setAnimationFrequency()
	setDrawPriority(DRAW_PRIORITY);
}
