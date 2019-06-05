#include "Shark.h"
#include "GameScreen.h"
#include "Flow.h"
#include "Bullet.h"

Shark::Shark(GameScreen& gameScreen, int numOfLife)
	: NPC(gameScreen, numOfLife)
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
	m_time.checkTimer();
}

void Shark::onCollide(Flow* flow)
{
	setExternaAlcceleration(flow->getFlowPower());
}


void Shark::onCollide(Bullet* bullet)
{
	if (!isDie()) {
		decreaseLife(bullet->getDamage());
		bullet->suicide();
	}
}

void Shark::playChoice(Direction lastDirection, bool isCollided)
{
	NPC::playChoice(lastDirection, isCollided);

	if (isDie())
		return;

	if (isCollided) {
		setDirection(getRandomDirect());
	}
	std::shared_ptr<Player> player = getGameScreen().getWorld().getBODS().getPlayer();
	float distanceFromPlayer = getDistance(player);
	if (distanceFromPlayer <= m_radiusAttack) {
		m_inChase = true;
		sf::Vector2f direction = getPosition() - player->getPosition();
		getInteralAcceleration().x = -direction.x*0.0000025f;
		getInteralAcceleration().y = -direction.y*0.0000025f;
		if (getPosition().x < player->getPosition().x) {
			setDirection(Direction::RIGHT);
		}
		else
			setDirection(Direction::LEFT);
	}
	else{
		m_inChase = false;
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

void Shark::init()
{
	setAnimation("shark_anim");
	setAnimationFrequency(70);
	setSize(getSharkSize());
	// TODO setDamage();
	setDrawPriority(DRAW_PRIORITY);
	m_radiusAttack = 5.f*getSize().x;
	setDirection(getRandomDirect());
	m_inChase = false;
	m_time.start(3000, [this] {
		if (!m_inChase) {
			/*Direction direct;
			if (isUpDirections(getLastDirection()))
				direct = getRandomDownDirections();
			else if (isDownDirections(getLastDirection()))
				direct = getRandomUPDirections();
			else if (isRightDirections(getLastDirection()))
				direct = getRandomLeftDirections();
			else 
				direct = getRandomRightDirections();*/

			setDirection(getRandomDirect());
		}
	});
}

const sf::Vector2i& Shark::getSharkSize()
{
	static sf::Vector2i SHARK_SIZE(static_cast<int>(getDefaultSize().x*0.95f), static_cast<int>(getDefaultSize().y*0.5f));
	return SHARK_SIZE;
}
