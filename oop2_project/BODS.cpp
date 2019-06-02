#include "BODS.h"
#include "ParseLevelException.h"

const std::shared_ptr<Player>& BODS::getPlayer() const
{
	if (!m_player)
		throw std::logic_error("Cannot get player, because player not in game!");
	return m_player;
}

void BODS::handleRequests()
{
	handleRemoveRequestsQueue();
	handleAddRequestsQueue();
}

void BODS::prepareLevel()
{
	handleRequests();
	connectPlayerMember();
}
/*
void BODS::clear()
{
	m_player = nullptr;
	while (!m_addQueue.empty()) m_addQueue.pop();
	while (!m_removeQueue.empty()) m_addQueue.pop();
	// TODO delete tree
}
*/

void BODS::handleAddRequestsQueue()
{
	while (!m_addQueue.empty()) {
		auto& bo = m_addQueue.front();
		addBO(bo);
		m_addQueue.pop();
	}
}

void BODS::handleRemoveRequestsQueue()
{
	while (!m_removeQueue.empty()) {
		auto& bo = m_removeQueue.front();
		removeBO(bo);
		m_removeQueue.pop();
	}
}

void BODS::addBO(const std::shared_ptr<BoardObject>& boardObject)
{
	m_boardObjects[boardObject->getDrawPriority()].insert(boardObject);
	int32 proxyId = m_aabbTree.CreateProxy(boardObject->getAABB(), static_cast<void*>(boardObject.get()));
	boardObject->setProxyId(proxyId);
	boardObject->setInGame(boardObject);
}

void BODS::removeBO(const std::shared_ptr<BoardObject>& boardObject)
{
	auto& currSet = m_boardObjects[boardObject->getDrawPriority()];
	auto it = currSet.find(boardObject);
	if (it != currSet.end()) {
		m_aabbTree.DestroyProxy(boardObject->getProxyId());
		currSet.erase(it);
	}	
}

string BODS::toString() const
{
	return "BODS: { " + buildBOStr() + ", numReqsAdd=" + std::to_string(m_addQueue.size()) + ", numReqsRemove=" +
			std::to_string(m_removeQueue.size()) + " }";
}

string BODS::buildBOStr() const
{
	string str = "BoardObjects: {\n";
	for (const auto& pair : m_boardObjects)
		for(const auto& bo : pair.second)
			str += bo->toString() + "\n";
	str += "}";
	return str;
}

void BODS::connectPlayerMember()
{
	// find player
	auto& playerSet = m_boardObjects[Player::DRAW_PRIORITY];
	for (auto& boardObject : playerSet) {
		// check if is player
		if (std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(boardObject)) {
			m_player = player;
			break;
		}
	}
	
	// check if not found player
	if (!m_player)
		throw ParseLevelException("Cannot find player at game");
}
