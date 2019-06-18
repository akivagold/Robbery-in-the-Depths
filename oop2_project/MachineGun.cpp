#include "MachineGun.h"
#include "BOFactory.h"
#include "Bullet.h"

// register
bool MachineGun::isRegisteredLeft = BOFactory::getInterface().registerIn(MachineGun::CHAR_LEFT_MG, [](GameScreen& gameScreen) { return std::make_shared<MachineGun>(gameScreen, Direction::LEFT); });
bool MachineGun::isRegisteredRight = BOFactory::getInterface().registerIn(MachineGun::CHAR_RIGHT_MG, [](GameScreen& gameScreen) { return std::make_shared<MachineGun>(gameScreen, Direction::RIGHT); });
bool MachineGun::isRegisteredUp = BOFactory::getInterface().registerIn(MachineGun::CHAR_UP_MG, [](GameScreen& gameScreen) { return std::make_shared<MachineGun>(gameScreen, Direction::UP); });
bool MachineGun::isRegisteredDown = BOFactory::getInterface().registerIn(MachineGun::CHAR_DOWN_MG, [](GameScreen& gameScreen) { return std::make_shared<MachineGun>(gameScreen, Direction::DOWN); });

// init
const float MachineGun::RADIUS_SHOT = static_cast<float>(BoardObject::getDefaultSize().x)*10.f;

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

void MachineGun::onCollide(Bullet* bullet)
{
	if (bullet->getMyOwner() == this) {
		bullet->isCollideWiteMyowner(true);
	}
}

#include <iostream>
void MachineGun::init()
{
	setDrawPriority(DRAW_PRIORITY);
	setSize(getDefaultSize());

	// set default weapon
	auto defWeapon = std::make_shared<AK47>(this);
	defWeapon->setInfLimit();
	setWeapon(defWeapon);

	if (getDirection() == Direction::RIGHT)
		setAnimation("machine_gun_right");
	else if (getDirection() == Direction::LEFT)
		setAnimation("machine_gun_left");
	else if (getDirection() == Direction::UP)
		setAnimation("machine_gun_up");
	else if (getDirection() == Direction::DOWN)
		setAnimation("machine_gun_down");

	int shootingTempo = 100 + rand() % 150;
	m_time.start(shootingTempo, [this] {
		if (shootingPauseClock.getElapsedTime().asSeconds() < SHOOTING_PAUSE_SECONDS) {
			float distanceFromPlayer = getRadiusFromPlayer();
			// fire
			if (distanceFromPlayer < RADIUS_SHOT)
				getGun()->useTool();	
		}
	
		if (shootingPauseClock.getElapsedTime().asSeconds() > SHOOTING_PAUSE_SECONDS * 2) {
			shootingPauseClock.restart();
		}
	});
}
