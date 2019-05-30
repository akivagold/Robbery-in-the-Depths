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
	m_boardObjects.insert(boardObject);
	int32 proxyId = m_aabbTree.CreateProxy(boardObject->getAABB(), static_cast<void*>(boardObject.get()));
	boardObject->setProxyId(proxyId);
	boardObject->setInGame();
}

void BODS::removeBO(const std::shared_ptr<BoardObject>& boardObject)
{
	auto it = m_boardObjects.find(boardObject);
	if (it != m_boardObjects.end()) {
		m_aabbTree.DestroyProxy(boardObject->getProxyId());
		m_boardObjects.erase(it);
	}	
}

string BODS::toString() const
{
	return "BODS: { " + buildBOStr() + ", numReqsAdd=" + std::to_string(m_addQueue.size()) + ", numReqsRemove=" +
			std::to_string(m_removeQueue.size()) + " }";
}

string BODS::buildBOStr() const
{
	string str = "BoardObjects: {";
	for (auto& bo : m_boardObjects)
		str += bo->toString() + "\n";
	str += " }";
	return str;
}

void BODS::connectPlayerMember()
{
	// find player
	for (auto& boardObject : m_boardObjects) {
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
