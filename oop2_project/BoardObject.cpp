#include "BoardObject.h"
#include "GameScreen.h"

// init 
const sf::Vector2i BoardObject::DEFAULT_SIZE(50, 50);

BoardObject::BoardObject(GameScreen& gameScreen, int drawPriority)
	: AnimationView(gameScreen.getWindow()), m_gameScreen(gameScreen), m_canMoveThroughMe(true), m_inGame(false)
{
	setDrawPriority(drawPriority);
	init();
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

float BoardObject::getDistance(const std::shared_ptr<BoardObject>& other) const
{
	return sqrt(pow(getPosition().x - other->getPosition().x, 2) + pow(getPosition().y - other->getPosition().y, 2));
}

string BoardObject::toString() const
{
	return "BoardObject: { drawPriority=" + std::to_string(m_drawPriority) + ", " + AnimationView::toString() + " }";
}

void BoardObject::updateComponents()
{
	AnimationView::updateComponents();

	if (isInGame())
		updateAABB();
}

void BoardObject::updateAABB()
{
	// TODO getGameScreen().getWorld().getBODS().getAABBTree().updateObject(this);
}

void BoardObject::init()
{
	setParent(getGameScreen().getWorld());
	setSize(BoardObject::DEFAULT_SIZE);
}
