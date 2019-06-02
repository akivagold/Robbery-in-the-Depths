#include "Projectile.h"

Projectile::Projectile(GameScreen& gameScreen, Direction direction)
	: MovingObject(gameScreen)
{
	init(direction);
}

void Projectile::init(Direction direction)
{
	setSize(BoardObject::getDefaultSize().x * 0.5, BoardObject::getDefaultSize().y * 0.5);
	//setDirection(direction);
}

