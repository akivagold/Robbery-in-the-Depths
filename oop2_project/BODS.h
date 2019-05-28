#pragma once
//---- include section ------
#include <string>
#include <set>
#include <queue>
#include "AABBTree.h"
#include "Player.h"
#include "BoardObject.h"

//---- using section --------
using std::string;

/*
 * BoardObjectDataStructure class
 */
class BODS
{
public:
	// custom compare board objects
	struct BOCompare
	{
		bool operator()(const std::shared_ptr<BoardObject>& lhs, const std::shared_ptr<BoardObject>& rhs) const
		{
			return lhs->getDrawPriority() < rhs->getDrawPriority();
		}
	};	
	// board data structure
	using BoardDS = std::multiset<std::shared_ptr<BoardObject>, BOCompare>;
	// constructor
	BODS() = default;
	// request add board object
	void requestAddBO(const std::shared_ptr<BoardObject>& boardObject) { m_addQueue.push(boardObject); }
	// request remove board object
	void requestRemoveBO(const std::shared_ptr<BoardObject>& boardObject) { m_removeQueue.push(boardObject); }
	// get AABB tree
	AABBTree<BoardObject>& getAABBTree() { return m_aabbTree; }
	// get board objects
	BoardDS& getBOs() { return m_boardObjects; }
	// get player
	const std::shared_ptr<Player>& getPlayer() const { return m_player; }
	// handle requests queues
	void handleRequests();
	// prepare level
	void prepareLevel();
	// clear
	//  void clear();                                           TODO
	// convert to string
	virtual string toString() const;
private:
	// player
	std::shared_ptr<Player> m_player;
	// all board objects
	BoardDS m_boardObjects;
	// add/remove request queues
	std::queue<std::shared_ptr<BoardObject>> m_addQueue, m_removeQueue;
	// AABB tree
	AABBTree<BoardObject> m_aabbTree;
	// handle add request queue
	void handleAddRequestsQueue();
	// handle remove request queue
	void handleRemoveRequestsQueue();
	// add board object
	void addBO(const std::shared_ptr<BoardObject>& boardObject);
	// remove board object
	void removeBO(const std::shared_ptr<BoardObject>& boardObject);
	// build BoardObjects as string
	string buildBOStr() const;
	// connect player member
	void connectPlayerMember();
};
