#include "Chest.h"
#include "Player.h"

Chest::Chest(GameScreen& gameScreen)
	: Container(gameScreen)
{
	init();
}

void Chest::pickup(Player* owner)
{
	Container::pickup(owner);

	// TODO add sound

	setAnimation("open_chest_anim");
	setAnimationFrequency(50);
	m_openChestSW.start(OPEN_CHEST_ANIM_TIME, [this] {
		vanish();
	});
}

void Chest::draw()
{
	Container::draw();
	m_openChestSW.checkStopWatch();
}

string Chest::toString() const
{
	return "Chest: { " + Container::toString() + " }";
}

void Chest::init()
{
	setAnimation("chest");
	setDrawPriority(DRAW_PRIORITY);
	setSize(getChestSize());
}

const sf::Vector2i& Chest::getChestSize()
{
	static sf::Vector2i CHEST_SIZE(static_cast<int>(getDefaultSize().x*0.55f), static_cast<int>(getDefaultSize().y*0.5f));
	return CHEST_SIZE;
}
