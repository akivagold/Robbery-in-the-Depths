#include "Shark.h"

Shark::Shark(GameScreen& gameScreen, int numOfLife)
	: NPC(gameScreen, numOfLife)
{
	init();
}

void Shark::init()
{
	setAnimation("life"); // TODO change animation
	//setAnimationFrequency(?)
	// TODO setDrawPriority()
	// TODO setDamge();
}
