#include "Rubber.h"
#include "Flow.h"
#include "GameScreen.h"


Rubber::Rubber(GameScreen& gameScreen, int numOfLife)
	: NPC(gameScreen, numOfLife), m_tool(std::make_shared<AK47>(this))
{
	init();
}

void Rubber::onDirectionChanged()
{
}

void Rubber::draw()
{
	NPC::draw();
	m_time.checkTimer();
}

void Rubber::onDie()
{
	NPC::onDie();
	//TODO setAnimation("die_crab");
}

void Rubber::onCollide(Flow* flow)
{
	setExternaAlcceleration(flow->getFlowPower());
}

void Rubber::playChoice(Direction lastDirection, bool isCollided)
{
	NPC::playChoice(lastDirection, isCollided);

	if (isDie())
		return;

	std::shared_ptr<Player> player = getGameScreen().getWorld().getBODS().getPlayer();
	float distanceFromPlayer = getRadiusFromPlayer();
	if (distanceFromPlayer <= m_radiusAttack) {
		//m_inChase = true;
		sf::Vector2f direction;
		direction = getPosition() - player->getPosition();
		if (getPosition().x < player->getPosition().x) {
			direction.x = direction.x + (1.f/3.f)*(player->getPosition().x - getPosition().x);
		}
		else {
			direction.x = direction.x - (1.f/3.f)*(getPosition().x - player->getPosition().x );
		}
		getInteralAcceleration().x = -direction.x*0.0000025f;
		getInteralAcceleration().y = -direction.y*0.0000025f;
	}
	else {
		//m_inChase = false;
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
#include <iostream>
void Rubber::init()
{
	setAnimation("rubber");
	setAnimationFrequency(70);
	// TODO setDamage();
	setDrawPriority(DRAW_PRIORITY);
	m_radiusAttack = 500;
	m_radiusShot = 100;
	setDirection(getRandomDirect());
	std::shared_ptr<Player> player = getGameScreen().getWorld().getBODS().getPlayer();
	m_time.start(3000, [this, &player] {
		if (getRadiusFromPlayer() <= m_radiusShot ) {
			std::cout << "fire" << std::endl;
			m_tool->useTool();
		}
	});

}
