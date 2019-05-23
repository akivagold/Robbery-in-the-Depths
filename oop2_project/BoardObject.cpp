#include "BoardObject.h"


BoardObject::BoardObject(sf::RenderWindow& window, GameScreen& gameScreen, int drawPriority)
	: AnimationView(window), m_gameScreen(gameScreen)
{
	setDrawPriority(drawPriority);
}

void BoardObject::setDrawPriority(int drawPriority)
{
	if (drawPriority < 0)
		throw std::out_of_range("Draw priority " + std::to_string(drawPriority) + " is illegal");
}

float BoardObject::getDistance(const BoardObject & other)
{
	return sqrt(pow(getPosition().x - other.getPosition().x, 2) + pow(getPosition().y - other.getPosition().y, 2));
}

string BoardObject::toString() const
{
	return "BoardObject: { " + AnimationView::toString() + " }";
}
