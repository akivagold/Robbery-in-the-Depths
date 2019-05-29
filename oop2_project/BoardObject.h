#pragma once
//---- include section ------
#include <string>
#include "AnimationView.h"
class GameScreen;
#include <math.h>
#include "IAABB.h"
#include "AABB.h"

//---- using section --------
using std::string;

/*
 * BoardObject class
 */
class BoardObject :
	public GUI::AnimationView, public IAABB
{
public:
	// default size in pixels
	static const sf::Vector2i DEFAULT_SIZE;
	// get AABB
	virtual AABB getAABB() const override;

	// TODO add: get collides objects

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
	virtual bool canMoveThroughMe() const { return m_canMoveThroughMe; }
	// change flag that object in game
	void setInGame() { m_inGame = true; }
	// check if object in game
	bool isInGame() const { return m_inGame; }
protected:
	// if another object can move through me
	bool m_canMoveThroughMe;                      // TODO need be private and use by function
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
	// update AABB
	void updateAABB();
	// init
	void init();
};

