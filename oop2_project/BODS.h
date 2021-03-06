#pragma once
//---- include section ------
#include <string>
#include <unordered_set>
#include <queue>
#include <Box2D/Box2D.h>
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
	// boardobjects data structure
	using BoardDS = std::map<int, std::unordered_set<std::shared_ptr<BoardObject>>>;
	// constructor
	BODS() = default;
	// request add board object
	void requestAddBO(const std::shared_ptr<BoardObject>& boardObject) { m_addQueue.push(boardObject); }
	// request remove board object
	void requestRemoveBO(const std::shared_ptr<BoardObject>& boardObject) { m_removeQueue.push(boardObject); }
	// get AABB tree
	b2DynamicTree& getAABBTree() { return m_aabbTree; }
	// get board objects
	BoardDS& getBOs() { return m_boardObjects; }
	// get player
	const std::shared_ptr<Player>& getPlayer() const;
	// handle requests queues
	void handleRequests();
	// prepare level
	void prepareLevel();
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
	b2DynamicTree m_aabbTree;
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
