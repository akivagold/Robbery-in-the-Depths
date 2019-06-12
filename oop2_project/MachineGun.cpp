#include "MachineGun.h"
#include "BOFactory.h"

// register
bool MachineGun::isRegisteredLeft = BOFactory::getInterface().registerIn(MachineGun::CHAR_LEFT_MG, [](GameScreen& gameScreen) { return std::make_shared<MachineGun>(gameScreen, Direction::LEFT); });
bool MachineGun::isRegisteredRight = BOFactory::getInterface().registerIn(MachineGun::CHAR_RIGHT_MG, [](GameScreen& gameScreen) { return std::make_shared<MachineGun>(gameScreen, Direction::RIGHT); });
bool MachineGun::isRegisteredUp = BOFactory::getInterface().registerIn(MachineGun::CHAR_UP_MG, [](GameScreen& gameScreen) { return std::make_shared<MachineGun>(gameScreen, Direction::UP); });
bool MachineGun::isRegisteredDown = BOFactory::getInterface().registerIn(MachineGun::CHAR_DOWN_MG, [](GameScreen& gameScreen) { return std::make_shared<MachineGun>(gameScreen, Direction::DOWN); });

// init
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

	int changeDirectionTime = 1000 + rand() % 1500;
	m_time.start(changeDirectionTime, [this] {
		float distanceFromPlayer = getRadiusFromPlayer();
		// fire
		if(distanceFromPlayer < RADIUS_SHOT)
			getGun()->useTool();
	});
}
