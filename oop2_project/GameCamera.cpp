#include "GameCamera.h"
#include "World.h"


GameCamera::GameCamera(World* world, const std::shared_ptr<Player> & player)
	:m_world(world), m_player(player)
{
}

void GameCamera::updateCamera()
{
	float elapsedTime = m_clock.getElapsedTime().asSeconds() * 100;
	m_clock.restart();
	sf::Vector2f cameraSize = m_world->getCamera().getSize();
	sf::Vector2f cameraCenter = m_world->getCamera().getCenter();
	sf::Vector2f cameraPreCenter = cameraCenter;
	sf::Vector2f cameraPos = cameraCenter - (cameraSize / 2.f);
	sf::Vector2f playerPos = m_player->getPosition();
	sf::Vector2f worldPos = m_world->getPosition();

	// update x axis
	m_world->getCamera().move(sf::Vector2f(elapsedTime * (playerPos.x - cameraCenter.x) / 50, 0.f));
	cameraCenter = m_world->getCamera().getCenter();
	cameraPos = cameraCenter - (cameraSize / 2.f);
	//check if update is OK
	if (!(abs(playerPos.x - cameraCenter.x) > cameraSize.x / 3 && (cameraPos.x > worldPos.x && cameraPos.x + cameraSize.x < worldPos.x + m_world->getWidth()))) {
		// return to pre update
		m_world->getCamera().setCenter(sf::Vector2f(cameraPreCenter.x, cameraCenter.y));
		cameraCenter = m_world->getCamera().getCenter();
		cameraPos = cameraCenter - (cameraSize / 2.f);
	}

	// update y axis
	m_world->getCamera().move(sf::Vector2f(0.f, elapsedTime * (playerPos.y - cameraCenter.y) / 25));
	cameraCenter = m_world->getCamera().getCenter();
	cameraPos = cameraCenter - (cameraSize / 2.f);
	//check if update is OK
	if (!(abs(playerPos.y - cameraCenter.y) > (cameraSize.y) / 4 && (cameraPos.y > worldPos.y && cameraPos.y + cameraSize.y < worldPos.y + m_world->getHeight()))) {
		// return to pre update
		m_world->getCamera().setCenter(sf::Vector2f(cameraCenter.x, cameraPreCenter.y));
		cameraCenter = m_world->getCamera().getCenter();
		cameraPos = cameraCenter - (cameraSize / 2.f);
	}
	std::cout << m_player->getPosition().y;
	std::cout << m_world->getCamera().getCenter().x << std::endl;
}
