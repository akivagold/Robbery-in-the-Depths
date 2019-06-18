#include "Shark.h"
#include "GameScreen.h"
#include "Flow.h"
#include "Bullet.h"
#include "Grenade.h"
#include "Explosion.h"
#include "BOFactory.h"

// register
bool Shark::isRegistered = BOFactory::getInterface().registerIn(Shark::CHAR, [](GameScreen& gameScreen) { return std::make_shared<Shark>(gameScreen); });

// init
const float Shark::RADIUS_ATTACK = static_cast<float>(BoardObject::getDefaultSize().x)*5.f;

Shark::Shark(GameScreen& gameScreen, int numOfLife)
	: NPC(gameScreen, numOfLife), m_isInThinking(false), m_isInRadiusFromPlayer(false)
{
	init();
}

void Shark::onDirectionChanged()
{
	if (isLeftDirections(getDirection())) {
		if (isFlipped()) {
			flipAnimation(); // turn left
		}
	}
	else if (isRightDirections(getDirection())) {
		if (!isFlipped()) {
			flipAnimation(); // turn right
		}
	}
}

void Shark::onDie()
{
	NPC::onDie();
	// TODO play sound
	setAnimation("die_shark");
}

void Shark::draw()
{
	NPC::draw();
	m_thinkingTime.checkTimer();
}

void Shark::onCollide(Flow* flow)
{
	setExternaAlcceleration(getExternaAlcceleration() + flow->getFlowPower());
}


void Shark::onCollide(Bullet* bullet)
{
	if (!isDie() && !bullet->isInShotTime()) {
		decreaseLife(bullet->getDamage());
		bullet->explode();
	}
}

void Shark::onCollide(Grenade* grenade)
{
	if (!isDie() && !grenade->isInShotTime()) {
		decreaseLife(grenade->getDamage());
		grenade->explode();
	}
}

void Shark::onCollide(Explosion* explosion)
{
	sf::Vector2f moveDir = getCenter() - explosion->getCenter();
	sf::Vector2f exAcc = explosion->getPower()*moveDir;
	exAcc.x /= float(getSize().x);
	exAcc.y /= float(getSize().y);
	setExternaAlcceleration(exAcc);
}

void Shark::onCollide(Wall* wall)
{
	if (wallRecoveryClock.getElapsedTime().asMilliseconds() < WALL_RECOVERY_TIME / 8) {
		m_isWallRecover = true;
	}
	checkWallRecoverClock();
}

void Shark::onCollide(Box* box)
{
	if (wallRecoveryClock.getElapsedTime().asMilliseconds() < WALL_RECOVERY_TIME / 8) {
		m_isWallRecover = true;
	}
	checkWallRecoverClock();
}

void Shark::onCollide(MachineGun* machineGun)
{
	if (wallRecoveryClock.getElapsedTime().asMilliseconds() < WALL_RECOVERY_TIME / 8) {
		m_isWallRecover = true;
	}
	checkWallRecoverClock();
}

void Shark::playChoice(Direction lastDirection, bool isCollided)
{
	NPC::playChoice(lastDirection, isCollided);

	if (isDie())
		return;

	if (isCollided) {
		m_isInThinking = true;
		setDirectionAfterCollid(lastDirection);
	}

	float distanceFromPlayer = getRadiusFromPlayer();
	if (distanceFromPlayer <= RADIUS_ATTACK && !m_isInThinking) {
		inRadiusFromPlayer();
	}
	else{
		m_isInRadiusFromPlayer = false;
		goByDirection(getDirection());
	}
}

void Shark::inRadiusFromPlayer()
{
	m_isInRadiusFromPlayer = true;
	std::shared_ptr<Player> player = getGameScreen().getWorld().getBODS().getPlayer();
	sf::Vector2f direction = getPosition() - player->getPosition();
	getInteralAcceleration().x = -direction.x*0.0000025f;
	getInteralAcceleration().y = -direction.y*0.0000025f;
	if (getPosition().x < player->getPosition().x) {
		setDirection(Direction::RIGHT);
	}
	else
		setDirection(Direction::LEFT);
}

void Shark::init()
{
	setAnimation("shark_anim");
	setAnimationFrequency(70);
	setDamage(DAMAGE);
	setSize(getSharkSize());
	setDrawPriority(DRAW_PRIORITY);
	setDirection(getRandomDirect());

	m_thinkingTime.start(3000, [this] {
		if (m_isInThinking)
			m_isInThinking = false;
	});
}

const sf::Vector2i& Shark::getSharkSize()
{
	static sf::Vector2i SHARK_SIZE(static_cast<int>(getDefaultSize().x*0.95f), static_cast<int>(getDefaultSize().y*0.5f));
	return SHARK_SIZE;
}
