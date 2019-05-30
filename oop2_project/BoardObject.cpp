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
	string str = "BoardObject: { proxyId=" + std::to_string(m_proxyId) + ", drawPriority=" + std::to_string(m_drawPriority);
	str += ", aabb: { lower: { x=" + std::to_string(m_aabb.lowerBound.x) + ", y=" + std::to_string(m_aabb.lowerBound.y) + " }";
	str += ", upper: { x=" + std::to_string(m_aabb.upperBound.x) + ", y=" + std::to_string(m_aabb.upperBound.y) + " }";
	str += ", " + AnimationView::toString() + " }";
	return str;
}

std::forward_list<BoardObject*> BoardObject::getCollidesList()
{
	struct QueryHandler
	{
		QueryHandler(GameScreen& gameScreen, BoardObject* self) 
			: m_gameScreen(gameScreen), m_self(self)
		{}

		GameScreen& m_gameScreen;
		std::forward_list<BoardObject*> m_collides;
		BoardObject* m_self;

		// callback from Box2D lib
		bool QueryCallback(int32 proxyId) {
			// check if isn't me
			if (proxyId != m_self->getProxyId()) {
				b2DynamicTree& aabbTree = m_gameScreen.getWorld().getBODS().getAABBTree();
				BoardObject* bo = static_cast<BoardObject*>(aabbTree.GetUserData(proxyId));
				m_collides.push_front(bo);
			}
			return true;
		}

		// build collides list
		std::forward_list<BoardObject*> quaryCollides() {
			b2DynamicTree& aabbTree = m_gameScreen.getWorld().getBODS().getAABBTree();
			aabbTree.Query(this, m_self->getAABB());
			return m_collides;
		}
	};

	QueryHandler quaryHandler(m_gameScreen, this);
	return quaryHandler.quaryCollides();
}

void BoardObject::updateComponents()
{
	AnimationView::updateComponents();
	updateAABB();
}

void BoardObject::updateAABB()
{
	// save last AABB
	b2AABB lastAABB = m_aabb;
	
	// update AABB member
	const sf::Vector2f& position = getPosition();
	const sf::Vector2i& size = getSize();
	m_aabb.lowerBound = b2Vec2(position.x, position.y);
	m_aabb.upperBound = b2Vec2(position.x + float(size.x), position.y + float(size.y));

	if (isInGame()) {
		// update in tree
		b2Vec2 displacement = m_aabb.GetCenter() - lastAABB.GetCenter();
		b2DynamicTree& aabbTree = getGameScreen().getWorld().getBODS().getAABBTree();
		aabbTree.MoveProxy(m_proxyId, m_aabb, displacement);
	}	
}

void BoardObject::init()
{
	setParent(getGameScreen().getWorld());
	setSize(BoardObject::DEFAULT_SIZE);
}
