#pragma once
//---- include section ------
#include <string>
#include <Box2D/Box2D.h>
#include "AnimationView.h"
class GameScreen;
#include <math.h>
#include <forward_list>
class Flow;
class MovingObject;

//---- using section --------
using std::string;

/*
 * BoardObject class
 */
class BoardObject :
	public GUI::AnimationView
{
public:
	// default size in pixels
	static const sf::Vector2i DEFAULT_SIZE;
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
	virtual void onCollide(const std::shared_ptr<BoardObject>& obj);
	virtual void onCollide(const std::shared_ptr<MovingObject>& obj){}
	//virtual void onCollide(const std::shared_ptr<Flow>& obj){}
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

