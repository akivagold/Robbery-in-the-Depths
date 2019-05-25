#include "GameObjectView.h"

GameObjectView::GameObjectView(sf::RenderWindow& window, const GameObjectInfo& gameObjectInfo)
	: ImageView(window), m_gameObjectInfo(gameObjectInfo)
{
	initComponents();
}

string GameObjectView::toString() const
{
	return "GameObjectView: { " + m_gameObjectInfo.toString() + ", " + ImageView::toString() + " }";
}

void GameObjectView::initComponents()
{
	getBorder().setSize(2);
	getBorder().setColor(sf::Color::Blue);
	getImage().setTexture(m_gameObjectInfo.getName());
}
