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
 *//*
class BODS
{
public:
	// constructor
	BODS() = default;
	// board data structure
	using BoardDS = std::set<std::shared_ptr<BoardObject>>;
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
	void handleRequestsQueues();
	// convert to string
	virtual string toString() const;
private:
	// player
	std::shared_ptr<Player> m_player;              // TODO need to set when level loaded
	// all board objects
	BoardDS m_boardObjects;                        // TODO need to sort by draw priority
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
};

*/