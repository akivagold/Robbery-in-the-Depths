#include "Explosion.h"
#include "SoundManager.h"

// init
const float Explosion::DEFAULT_POWER = 0.01f;

Explosion::Explosion(GameScreen& gameScreen, float power)
	: InteractableObject(gameScreen)
{
	setPower(power);
	init();
}

void Explosion::onJoinedGame()
{
	m_vanishSW.start(SHOW_TIME, [this] {
		vanish();
	});

	playSound("explosion");
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
