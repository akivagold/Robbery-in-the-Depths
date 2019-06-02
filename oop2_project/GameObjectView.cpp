#include "GameObjectView.h"

GameObjectView::GameObjectView(sf::RenderWindow& window)
	: ImageView(window)
{
	initComponents();
}

void GameObjectView::setGOI(const GameObjectInfo& goi)
{
	m_gameObjectInfo = goi;
	getImage().setTexture(m_gameObjectInfo.getName());
}

string GameObjectView::toString() const
{
	return "GameObjectView: { " + m_gameObjectInfo.toString() + ", " + ImageView::toString() + " }";
}

void GameObjectView::initComponents()
{
	getBorder().setSize(2);
	getBorder().setColor(sf::Color::Blue);	
}
