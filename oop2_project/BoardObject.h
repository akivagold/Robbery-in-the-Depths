#pragma once
//---- include section ------
#include <string>
#include "AnimationView.h"
#include "GameScreen.h"
#include <math.h>

//---- using section --------
using std::string;

/*
 * BoardObject class
 */
class BoardObject :
	public GUI::AnimationView
{
public:
	// constructor
	explicit BoardObject(sf::RenderWindow& window, GameScreen& gameScreen,  int drawPriority = 0); 
	//set draw priority
	void setDrawPriority(int drawPriority);
	// get main screen
	const GameScreen& getGameScreen() const { return m_gameScreen; }
	// get draw priority
	int getDrawPriority() const { return m_drawPriority; }
	// check if collide with another
	bool isCollideWith(const BoardObject& other) const { return getBound().intersects(other.getBound()); }
	// get distance from another object
	float getDistance(const BoardObject& other) const;
	// update AABB
	void updateAABB() {} 
	// convert to string
	virtual string toString() const override;
private:
	// draw priority
	int m_drawPriority;
	// game screen
	GameScreen& m_gameScreen;
};

