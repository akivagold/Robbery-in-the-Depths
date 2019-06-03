#include "Crab.h"
#include "Flow.h"
#include "Wall.h"

// init
const float Crab::MIN_PLAYER_RADIUS = static_cast<float>(BoardObject::getDefaultSize().x)*4.f;

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

void Crab::onCollide(Wall* wall)
{
	if (isAboveThen(wall->getSelf())) {
		getInteralAcceleration().y = 0.f;
		setPosition(getPosition().x, wall->getPosition().y - getSize().y - 2);
	}
	else if (isLeftThen(wall->getSelf())) {
		getInteralAcceleration().x = 0.f;
		setDirection(Direction::LEFT);
	}
	else if (isRightThen(wall->getSelf())) {
		getInteralAcceleration().x = 0.f;
		setDirection(Direction::RIGHT);
	}
}

void Crab::onCollide(Flow* flow)
{
	setExternaAlcceleration(flow->getFlowPower());
}

void Crab::playChoice(Direction lastDirection, bool isCollided)
{
	if (isCollided) {
		getInteralAcceleration().y = 0;
	} else {
		getInteralAcceleration().y = 0.00005f*getMODefSize().y;
	}

	if (getSpeed().y > 0.001f*getMODefSize().y) {
		getInteralAcceleration().x = 0;
	} else {
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
