#include "Box.h"
#include "Projectile.h"
#include "Bullet.h"
#include "Grenade.h"
#include "BOFactory.h"

// register
bool Box::isRegistered = BOFactory::getInterface().registerIn(Box::CHAR, [](GameScreen& gameScreen) { return std::make_shared<Box>(gameScreen); });


Box::Box(GameScreen& gameScreen, int durabilityState)
	: StaticObject(gameScreen)
{
	setDurabilityState(durabilityState);
	init();
}

void Box::decreaseDurabilityState(int relDS)
{
	int newDS = getDurabilityState() - relDS;
	if (newDS < 0)
		newDS = 0;
	setDurabilityState(newDS);
}

void Box::setDurabilityState(int durabilityState)
{
	if (durabilityState == 0)
		destroy();
	if (!isLegalDurabilityState(durabilityState))
		throw std::out_of_range("Durability state (=" + std::to_string(durabilityState) + ") must be bigger or equals to zero");
	m_durabilityState = durabilityState;
}

void Box::destroy()
{
	playSound("box_explode");
	vanish();
}

void Box::init()
{
	setAnimation("box");
	setDrawPriority(DRAW_PRIORITY);
}
