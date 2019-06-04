#include "Projectile.h"

Projectile::Projectile(GameScreen& gameScreen, Character* owner,  Direction direction)
	: MovingObject(gameScreen), m_owner(owner)
{
	init(direction);
}

void Projectile::init(Direction direction)
{
	setSize(static_cast<int>(BoardObject::getDefaultSize().x * 0.5), static_cast<int>(BoardObject::getDefaultSize().y * 0.5));
	setDrawPriority(DRAW_PRIORITY);
	//setDirection(direction);
}

