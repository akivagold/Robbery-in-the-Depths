#include "Shark.h"
#include "GameScreen.h"

Shark::Shark(GameScreen& gameScreen, int numOfLife)
	: NPC(gameScreen, numOfLife)
{
	init();
}

void Shark::onDirectionChanged()
{
	if (getDirection() == Direction::LEFT || getDirection() == Direction::UP_LEFT || getDirection() == Direction::DOWN_LEFT) {
		if (isFlipped()) {
			flipAnimation(); // turn left
		}
	}
	else if (getDirection() == Direction::RIGHT || getDirection() == Direction::UP_RIGHT || getDirection() == Direction::DOWN_RIGHT) {
		if (!isFlipped()) {
			flipAnimation(); // turn right
		}
	}
}

void Shark::draw()
{
	NPC::draw();
	m_time.checkTimer();
}

void Shark::playChoice(Direction lastDirection, bool isCollided)
{
	if (isCollided) {
		setDirection(getRandomDirect());
	/*	if(isUpDirections(lastDirection))
			setDirection(getRandomDownDirections());
		if (isDownDirections(lastDirection))
			setDirection(getRandomUPDirections());
		if (isRightDirections(lastDirection))
			setDirection(getRandomLeftDirections());
		if (isLeftDirections(lastDirection))
			setDirection(getRandomRightDirections());*/
	}
	std::shared_ptr<Player> player = getGameScreen().getWorld().getBODS().getPlayer();
	float distanceFromPlayer = getDistance(player);
	if (distanceFromPlayer <= m_radiusAttack) {
		m_inChase = true;
		sf::Vector2f direction = getPosition() - player->getPosition();
		getInteralAcceleration().x = -direction.x*0.0000025f;
		getInteralAcceleration().y = -direction.y*0.0000025f;
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
	// TODO setDamage();
	setDrawPriority(DRAW_PRIORITY);
	m_radiusAttack = 1000;
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
