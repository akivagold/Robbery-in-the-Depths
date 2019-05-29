#include "Shark.h"
#include "GameScreen.h"

Shark::Shark(GameScreen& gameScreen, int numOfLife)
	: NPC(gameScreen, numOfLife)
{
	init();
}

void Shark::playChoice()
{
	std::shared_ptr<Player> player = getGameScreen().getWorld().getBODS().getPlayer();
	float distanceFromPlayer = getDistance(player);
	if (distanceFromPlayer <= m_radiusAttak) {
		sf::Vector2f direction = getPosition() - player->getPosition();
		getSpeed().x = -direction.x*0.0005f;
		getSpeed().y = -direction.y*0.0005f;
	}
	else{
		float offset = 2;
		switch (getRandomDirect())
		{
			case Direction::UP: {
				getSpeed().y = -offset;
			}break;
			case Direction::UP_RIGHT: {
				getSpeed().y = -offset;
				getSpeed().x = offset;
			} break;
			case Direction::RIGHT: {
				getSpeed().x = offset;
			} break;
			case Direction::DOWN_RIGHT: {
				getSpeed().y = offset;
				getSpeed().x = offset;
			} break;
			case Direction::DOWN: {
				getSpeed().y = offset;
			} break;
			case Direction::DOWN_LEFT: {
				getSpeed().y = offset;
				getSpeed().x = -offset;
			} break;
			case Direction::LEFT: {
				getSpeed().y = offset;
			} break;
			case Direction::UP_LEFT: {
				getSpeed().y = -offset;
				getSpeed().x = -offset;
			} break;
		}
		
	}

}

void Shark::init()
{
	setAnimation("life"); // TODO change animation
	m_radiusAttak = 1000;
	//setAnimationFrequency(?)
	// TODO setDrawPriority()
	// TODO setDamge();
}
