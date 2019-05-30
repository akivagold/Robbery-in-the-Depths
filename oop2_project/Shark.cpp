#include "Shark.h"
#include "GameScreen.h"

Shark::Shark(GameScreen& gameScreen, int numOfLife)
	: NPC(gameScreen, numOfLife)
{
	init();
}

void Shark::draw()
{
	NPC::draw();
	m_time.checkTimer();
}

void Shark::playChoice()
{
	Direction direct = getDirection();
	std::shared_ptr<Player> player = getGameScreen().getWorld().getBODS().getPlayer();
	float distanceFromPlayer = getDistance(player);
	if (distanceFromPlayer <= m_radiusAttak) {
		m_inChase = true;
		sf::Vector2f direction = getPosition() - player->getPosition();
		getInteralAcceleration().x = -direction.x*0.000025f;
		getInteralAcceleration().y = -direction.y*0.000025f;
	}
	else{
		m_inChase = false;
		float offset = 0.00025;
		//Direction direct = getDirection();
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
	setAnimation("life"); // TODO change animation
	m_radiusAttak = 1000;
	setDirection(getRandomDirect());
	m_inChase = false;
	m_time.start(3000, [this] {
		if(!m_inChase)
			setDirection(getRandomDirect());
	});
	//setAnimationFrequency(?)
	// TODO setDrawPriority()
	// TODO setDamge();
}
