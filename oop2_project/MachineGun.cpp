#include "MachineGun.h"



MachineGun::MachineGun(GameScreen& gameScreen, MovingObject::Direction directoin)
	: NPC(gameScreen, DEFAULT_LIFE), m_gun(nullptr)
{
	setDirection(directoin);
	init();
}

void MachineGun::draw()
{
	NPC::draw();
	m_time.checkTimer();
}


void MachineGun::init()
{
	setAnimation("coin");
	setDrawPriority(DRAW_PRIORITY);

	int changeDirectionTime = 1000 + rand() % 1500;
	m_time.start(changeDirectionTime, [this] {
		// fire
		getGun()->useTool();
	});
}
