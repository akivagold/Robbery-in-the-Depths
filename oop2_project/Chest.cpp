#include "Chest.h"
#include "Player.h"

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
	setAnimation("chest");
	//setAnimation("open_chest_anim");
	//setAnimationFrequency(50);
	setDrawPriority(DRAW_PRIORITY);
}
