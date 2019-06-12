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
class Rubber;
class Flow;
class Bullet;
class Chest;
class MachineGun;
class Grenade;
class Explosion;
class Box;

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
	// get distance from another board object
	float getDistance(const std::shared_ptr<BoardObject>& other) const;
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
	// get collides list - log(n) complexity
	std::forward_list<BoardObject*> getCollidesList();
	// get self
	const std::shared_ptr<BoardObject>& getSelf() const;
	// get default size of object
	static const sf::Vector2i& getDefaultSize();
	// event when object joined to game
	virtual void onJoinedGame() { };
	// vanish from map
	void vanish();
	// check if object if above then another object
	bool isAboveThen(const std::shared_ptr<BoardObject>& other) const { return (getPosition().y + getSize().y < other->getPosition().y); }
	// check if object if left then another object
	bool isLeftThen(const std::shared_ptr<BoardObject>& other) const { return (getPosition().x + getSize().x < other->getPosition().x); }
	// check if object if right then another object
	bool isRightThen(const std::shared_ptr<BoardObject>& other) const { return (other->getPosition().x + other->getSize().x < getPosition().x); }
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) = 0;
	virtual void onCollide(Player* player) = 0;
	virtual void onCollide(Shark* shark) = 0;
	virtual void onCollide(Crab* crab) = 0;
	virtual void onCollide(Rubber* rubber) = 0;
	virtual void onCollide(Chest* chest) = 0;
	virtual void onCollide(Wall* wall) = 0;
	virtual void onCollide(Flow* flow) = 0;
	virtual void onCollide(Bullet* bullet) = 0;
	virtual void onCollide(MachineGun* machineGun) = 0;
	virtual void onCollide(Grenade* grenade) = 0;
	virtual void onCollide(Explosion* explosion) = 0;
	virtual void onCollide(Box* box) = 0;
	// convert to string
	virtual string toString() const override;
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
