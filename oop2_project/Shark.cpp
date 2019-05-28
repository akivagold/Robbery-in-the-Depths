#include "Shark.h"

Shark::Shark(sf::RenderWindow& window, GameScreen& gameScreen, int numOfLife)
	: NPC(window, gameScreen, numOfLife)
{
	init();
}

void Shark::init()
{
	setAnimation("life"); // TODO change animation
	// TODO setDrawPriority()
	// TODO setDamge();
}
