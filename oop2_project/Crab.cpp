#include "Crab.h"
#include "Flow.h"
#include "Wall.h"
#include "Box.h"
#include "Bullet.h"
#include "Grenade.h"
#include "Explosion.h"
#include "BOFactory.h"

// register
bool Crab::isRegistered = BOFactory::getInterface().registerIn(Crab::CHAR, [](GameScreen& gameScreen) { return std::make_shared<Crab>(gameScreen); });

// init
const float Crab::MIN_PLAYER_RADIUS = static_cast<float>(BoardObject::getDefaultSize().x)*2.f;

Crab::Crab(GameScreen& gameScreen, int numOfLife)
	: NPC(gameScreen, numOfLife), m_isPlayerInRadius(false)
{
	init();
}

void Crab::draw()
{
	NPC::draw();
	m_timer.checkTimer();
}

void Crab::onDie()
{
	NPC::onDie();
	setAnimation("die_crab");
}

// on collide on solid
void Crab::onCollideSoild(BoardObject* bo) 
{
	if (isDie())
		return;

	if (isAboveThen(bo->getSelf())) {
		getInteralAcceleration().y = 0.f;
		setPosition(getPosition().x, getPosition().y - 2);
	}
	else if (isLeftThen(bo->getSelf())) {
		getInteralAcceleration().x = 0.f;
		setDirection(Direction::LEFT);
	}
	else if (isRightThen(bo->getSelf())) {
		getInteralAcceleration().x = 0.f;
		setDirection(Direction::RIGHT);
	}
}

void Crab::onCollide(Wall* wall)
{
	onCollideSoild(wall);
}

void Crab::onCollide(Box* box)
{
	onCollideSoild(box);
}

void Crab::onCollide(Flow* flow)
{
	setExternaAlcceleration(flow->getFlowPower());
}

void Crab::onCollide(Bullet* bullet)
{
	if (!isDie() && !bullet->isInShotTime()) {
		decreaseLife(bullet->getDamage());
		bullet->explode();
	}
}

void Crab::onCollide(Grenade* grenade)
{
	if (!isDie() && !grenade->isInShotTime()) {
		decreaseLife(grenade->getDamage());
		grenade->explode();
	}
}

void Crab::onCollide(Explosion* explosion)
{
	sf::Vector2f moveDir = getCenter() - explosion->getCenter();
	sf::Vector2f exAcc = explosion->getPower()*moveDir;
	exAcc.x /= float(getSize().x);
	exAcc.y /= float(getSize().y);
	setExternaAlcceleration(exAcc);
}

void Crab::playChoice(Direction lastDirection, bool isCollided)
{
	NPC::playChoice(lastDirection, isCollided);

	if (isDie())
		return;

	if (isCollided) {
		getInteralAcceleration().y = 0;
	}
	else {
		getInteralAcceleration().y = 0.00005f*getMODefSize().y;
	}

	if (getSpeed().y > 0.001f*getMODefSize().y) {
		getInteralAcceleration().x = 0;
	}
	else {
		if (getDirection() == Direction::RIGHT) {
			getInteralAcceleration().x = 0.00005f*getMODefSize().x;
		}
		else {
			getInteralAcceleration().x = -0.00005f*getMODefSize().x;
		}
	}

	// check if user in my radius
	if (getRadiusFromPlayer() <= MIN_PLAYER_RADIUS) {
		if (!m_isPlayerInRadius) {
			setAnimation("adhd_crab");
			m_isPlayerInRadius = true;
		}
	}
	else {
		if (m_isPlayerInRadius) {
			setAnimation("walking_crab");
			m_isPlayerInRadius = false;
		}
	}
}

void Crab::init()
{
	setAnimation("walking_crab");
	setAnimationFrequency(30);
	setDrawPriority(DRAW_PRIORITY);
	setDamage(DAMAGE);
	setDirection(getRandomLeftRightDirect());
	setSize(getCrabSize());

	int changeDirectionTime = 2000 + rand() % 4000;
	m_timer.start(changeDirectionTime, [this]() {
		Direction direction = getRandomLeftRightDirect();
		setDirection(direction);
		getInteralAcceleration().x = 0;
	});

}

const sf::Vector2i& Crab::getCrabSize()
{
	static sf::Vector2i CRAB_SIZE(static_cast<int>(getDefaultSize().x*0.5f), static_cast<int>(getDefaultSize().y*0.5f));
	return CRAB_SIZE;
}


