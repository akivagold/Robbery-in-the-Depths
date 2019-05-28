#include "Shark.h"

Shark::Shark(sf::RenderWindow& window, GameScreen& gameScreen, int numOfLife)
	: NPC(window, gameScreen, numOfLife)
{
	init();
	// TODO setDamge();
}

void Shark::init()
{
	setAnimation("life");
}
