#include "Explosion.h"
#include "SoundManager.h"

Explosion::Explosion(GameScreen& gameScreen)
	: InteractableObject(gameScreen)
{
	init();
}

void Explosion::onJoinedGame()
{
	m_vanishSW.start(SHOW_TIME, [this] {
		vanish();
	});

	GUI::SoundManager::getInterface().playSound("explosion");
}

void Explosion::draw()
{
	InteractableObject::draw();
	m_vanishSW.checkStopWatch();
}

void Explosion::init()
{
	setAnimation("explosion");
	setAnimationFrequency(ANIM_FREQUENCY);
	setDamage(DAMAGE);
	setDrawPriority(DRAW_PRIORITY);
}
