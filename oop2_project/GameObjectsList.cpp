#include "GameObjectsList.h"
#include "GOIFileParser.h"

GameObjectsList::GameObjectsList(sf::RenderWindow& window, const std::vector<GameObjectInfo>& gois)
	: BaseClass(window)
{
	initComponents(gois);
}

void GameObjectsList::addGOVClickListener(std::function<void(const std::shared_ptr<GameObjectView>&)> onGOVClicked)
{
	for (auto& gameObject : m_gameObjects) {
		gameObject->addClickListener([onGOVClicked, &gameObject](GUI::View& view) {
			onGOVClicked(gameObject);
		});
	}
}

string GameObjectsList::toString() const
{
	return "GameObjectsList: { " + BaseClass::toString() + " }";
}

void GameObjectsList::initComponents(const std::vector<GameObjectInfo>& gois)
{
	getBackground().setColor(sf::Color(235, 255, 247));

	// add game object views
	for (const GameObjectInfo& goi : gois) {
		// create GameObjectView
		std::shared_ptr<GameObjectView> gov = std::make_shared<GameObjectView>(getWindow());
		gov->setGOI(goi);
		m_gameObjects.push_back(gov);
		addView(gov);
	}
}
