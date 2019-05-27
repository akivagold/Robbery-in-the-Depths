#include "BODS.h"

void BODS::handleRequests()
{
	handleRemoveRequestsQueue();
	handleAddRequestsQueue();
}

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
	m_aabbTree.insertObject(&(*boardObject));
}

void BODS::removeBO(const std::shared_ptr<BoardObject>& boardObject)
{
	auto it = m_boardObjects.find(boardObject);
	if (it != m_boardObjects.end()) {
		m_boardObjects.erase(it);
		m_aabbTree.insertObject(&(*boardObject));
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
