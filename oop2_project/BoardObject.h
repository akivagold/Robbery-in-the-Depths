#pragma once
//---- include section ------
#include <string>
#include <Box2D/Box2D.h>
#include <cmath>
#include <forward_list>
#include "AnimationView.h"
class GameScreen;
class Player;
class Shark;
class Chest;
class Crab;
class Wall;
class Cop;
class Flow;
class Bullet;
class Chest;

//---- using section --------
using std::string;

/*
 * BoardObject class
 */
class BoardObject :
	public GUI::AnimationView
{
public:
	// get AABB
	const b2AABB& getAABB() const { return m_aabb; }
	// set draw priority
	void setDrawPriority(int drawPriority);
	// get main screen
	GameScreen& getGameScreen() { return m_gameScreen; }
	const GameScreen& getGameScreen() const { return m_gameScreen; }
	// get draw priority
	int getDrawPriority() const { return m_drawPriority; }
	// check if collide with another
	bool isCollideWith(const BoardObject& other) const { return getBound().intersects(other.getBound()); }
	// get distance from another object
	float getDistance(const std::shared_ptr<BoardObject>& other) const;
	// convert to string
	virtual string toString() const override;
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const = 0;
	// change flag that object in game
	void setInGame(const std::shared_ptr<BoardObject>& self);
	// check if object in game
	bool isInGame() const { return m_inGame; }
	// get proxy id
	int32 getProxyId() const { return m_proxyId; }
	// set proxy id
	void setProxyId(int32 proxyId) { m_proxyId = proxyId; }
	// get collides list
	std::forward_list<BoardObject*> getCollidesList();
	// get self
	const std::shared_ptr<BoardObject>& getSelf() const;
	// get default size of object
	static const sf::Vector2i& getDefaultSize();
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) = 0;
	virtual void onCollide(Player* player) = 0;
	virtual void onCollide(Shark* shark) = 0;
	virtual void onCollide(Crab* crab) = 0;
	virtual void onCollide(Cop* cop) = 0;
	virtual void onCollide(Chest* chest) = 0;
	virtual void onCollide(Wall* wall) = 0;
	virtual void onCollide(Flow* flow) = 0;
	virtual void onCollide(Bullet* bullet) = 0;
protected:
	// update components
	virtual void updateComponents() override;
	// constructor
	explicit BoardObject(GameScreen& gameScreen, int drawPriority = 0);
private:
	// flag that check if object in game
	bool m_inGame;
	// draw priority
	int m_drawPriority;
	// game screen
	GameScreen& m_gameScreen;
	// AABB
	b2AABB m_aabb;
	// proxy id (for AABB tree)
	int32 m_proxyId;
	// self
	std::shared_ptr<BoardObject> m_self;
	// update AABB
	void updateAABB();
	// init
	void init();
};

