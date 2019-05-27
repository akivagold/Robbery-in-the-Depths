#include "BoardObject.h"

BoardObject::BoardObject(sf::RenderWindow& window, GameScreen& gameScreen, int drawPriority)
	: AnimationView(window), m_gameScreen(gameScreen)
{
	setDrawPriority(drawPriority);
}

AABB BoardObject::getAABB() const
{
	const sf::Vector2f& position = getPosition();
	const sf::Vector2i& size = getSize();
	return AABB(position.x, position.y, position.x + size.x, position.y + size.y);
}

void BoardObject::setDrawPriority(int drawPriority)
{
	if (drawPriority < 0)
		throw std::out_of_range("Draw priority " + std::to_string(drawPriority) + " is illegal");
	m_drawPriority = drawPriority;
}

float BoardObject::getDistance(const BoardObject& other) const
{
	return sqrt(pow(getPosition().x - other.getPosition().x, 2) + pow(getPosition().y - other.getPosition().y, 2));
}

string BoardObject::toString() const
{
	return "BoardObject: { drawPriority=" + std::to_string(m_drawPriority) + ", " + AnimationView::toString() + " }";
}
