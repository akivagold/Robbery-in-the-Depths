#include "Trap.h"



void Trap::draw()
{
	InteractableObject::draw();
	play();
}

Trap::Trap(GameScreen& gameScreen)
	: InteractableObject(gameScreen)
{}
