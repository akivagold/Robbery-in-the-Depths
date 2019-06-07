#include "Projectile.h"

void Projectile::explode()
{
	suicide();
}

Projectile::Projectile(GameScreen& gameScreen, Character* owner,  Direction direction)
	: MovingObject(gameScreen, direction), m_owner(owner)
{
	init();
}

void Projectile::init()
{
	setSize(static_cast<int>(BoardObject::getDefaultSize().x*0.3f), static_cast<int>(BoardObject::getDefaultSize().y*0.3f));
	setDrawPriority(DRAW_PRIORITY);
}

