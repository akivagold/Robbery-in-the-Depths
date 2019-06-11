#include "MachineGun.h"


const float MachineGun::RADIUS_SHOT = static_cast<float>(BoardObject::getDefaultSize().x)*15.f;

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
	setDrawPriority(DRAW_PRIORITY);
	if (getDirection() == Direction::RIGHT || getDirection() == Direction::LEFT)
		setAnimation("machine_gun");
	else if (getDirection() == Direction::UP)
		setAnimation("machine_gun_up");
	else if (getDirection() == Direction::DOWN)
		setAnimation("machine_gun_down");

	if (getDirection() == Direction::LEFT) {
		flipAnimation();
	}
	int changeDirectionTime = 1000 + rand() % 1500;
	m_time.start(changeDirectionTime, [this] {
		float distanceFromPlayer = getRadiusFromPlayer();
		// fire
		if(distanceFromPlayer < RADIUS_SHOT)
			getGun()->useTool();
	});
}
