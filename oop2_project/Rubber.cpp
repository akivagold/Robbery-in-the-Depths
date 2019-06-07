#include "Rubber.h"
#include "Flow.h"
#include "GameScreen.h"
#include "Bullet.h"
#include "Grenade.h"

// init
const float Rubber::RADIUS_ATTACK = static_cast<float>(BoardObject::getDefaultSize().x)*10.f;
const float Rubber::RADIUS_SHOT = static_cast<float>(BoardObject::getDefaultSize().x)*5.f;

Rubber::Rubber(GameScreen& gameScreen, int numOfLife)
	: NPC(gameScreen, numOfLife), m_tool(std::make_shared<AK47>(this)),
	m_isInRadiusShot(false), m_isInRadiusfromPlayer(false)
{
	init();
}

void Rubber::onDirectionChanged()
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

void Rubber::draw()
{
	NPC::draw();
	m_time.checkTimer();
}

void Rubber::onDie()
{
	NPC::onDie();
	setAnimation("rubber_die");
}

void Rubber::onCollide(Flow* flow)
{
	setExternaAlcceleration(flow->getFlowPower());
	m_isInRadiusShot = false;
}

void Rubber::onCollide(Bullet* bullet)
{
	if (isDie())
		return;

	if (bullet->getMyOwner() != this) {
		decreaseLife(bullet->getDamage());
		bullet->explode();
	}
}

void Rubber::onCollide(Grenade* grenade)
{
	if (!isDie()) {
		decreaseLife(grenade->getDamage());
		grenade->explode();
	}
}

void Rubber::playChoice(Direction lastDirection, bool isCollided)
{
	NPC::playChoice(lastDirection, isCollided);

	if (isDie())
		return;
	
	std::shared_ptr<Player> player = getGameScreen().getWorld().getBODS().getPlayer();
	float distanceFromPlayer = getRadiusFromPlayer();
	if (distanceFromPlayer <= RADIUS_ATTACK) {
		inRadiusFromPlayer();
	}
	else {
		m_isInRadiusfromPlayer = false;
		float offset = 0.00025f;
		Direction direct = getDirection();
		switch (direct)
		{
		case Direction::UP: {
			getInteralAcceleration().y = -offset;
		} break;
		case Direction::UP_RIGHT: {
			getInteralAcceleration().y = -offset;
			getInteralAcceleration().x = offset;
		} break;
		case Direction::RIGHT: {
			getInteralAcceleration().x = offset;
		} break;
		case Direction::DOWN_RIGHT: {
			getInteralAcceleration().y = offset;
			getInteralAcceleration().x = offset;
		} break;
		case Direction::DOWN: {
			getInteralAcceleration().y = offset;
		} break;
		case Direction::DOWN_LEFT: {
			getInteralAcceleration().y = offset;
			getInteralAcceleration().x = -offset;
		} break;
		case Direction::LEFT: {
			getInteralAcceleration().y = offset;
		} break;
		case Direction::UP_LEFT: {
			getInteralAcceleration().y = -offset;
			getInteralAcceleration().x = -offset;
		} break;
		}
	}
}

void Rubber::init()
{
	setAnimation("rubber_swim");
	setAnimationFrequency(70);
	getTool()->setInfLimit();
	setDrawPriority(DRAW_PRIORITY);
	setDirection(getRandomDirect());

	int changeDirectionTime = 2000 + rand() % 4000;
	m_time.start(changeDirectionTime, [this] {
		if (isDie())
			return;

		// rand direction
		if (!m_isInRadiusfromPlayer)
			setDirection(getRandomDirect());
		
		// fire
		if (m_isInRadiusShot) {
			m_tool->useTool();
		}
	});

}

void Rubber::inRadiusFromPlayer()
{
	std::shared_ptr<Player> player = getGameScreen().getWorld().getBODS().getPlayer();
	m_isInRadiusfromPlayer = true;
	sf::Vector2f direction;
	direction = getPosition() - player->getPosition();
	if (getPosition().x < player->getPosition().x) {
		direction.x = direction.x + (0.5f)*(player->getPosition().x - getPosition().x);
		setDirection(Direction::RIGHT);
	}
	else {
		direction.x = direction.x - (0.5f)*(getPosition().x - player->getPosition().x);
		setDirection(Direction::LEFT);
	}
	getInteralAcceleration().x = -direction.x*0.0000025f;
	getInteralAcceleration().y = -direction.y*0.0000025f;

	// prepare to shot
	if ((getPosition().y >= (player->getPosition().y - getSize().y / 2)
		&& getPosition().y <= (player->getPosition().y + getSize().y / 2))
		&& getRadiusFromPlayer() <= RADIUS_SHOT) {
		if (!m_isInRadiusShot) {
			setAnimation("rubber_fire");
			m_isInRadiusShot = true;
			getSpeed().x = 0;
		    getSpeed().y = 0;
		}
		getInteralAcceleration().x = 0;
		getInteralAcceleration().y = 0;
	}
	else {
		if (m_isInRadiusShot) {
			setAnimation("rubber_swim");
			m_isInRadiusShot = false;
		}
	}
}
