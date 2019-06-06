#pragma once
//---- include section ------
#include <string>
#include "Character.h"
#include "Tool.h"

//---- using section --------
using std::string;

/*
 * Player class
 */
class Player :
	public Character
{
public:
	// draw priority
	static const int DRAW_PRIORITY = 100;
	// char
	static const char CHAR = 'p';
	// constructor
	explicit Player(GameScreen& gameScreen, int numOfLife = DEFAULT_LIFE);
	// add new tool
	void addTool(const std::shared_ptr<Tool>& tool);
	// get tool
	const std::shared_ptr<Tool>& getTool(Tool::ToolType toolType) const;
	// check if the player without tools
	bool isWithoutTools() const { return (m_tools.size() == 0); }
	// check if the player without tools
	bool haveCurrTool() const { return bool(m_currTool); }
	// get number of tools
	int getNumOfTool() const { return int(m_tools.size()) - 1; }
	// get score
	int getNumOfScore() const { return m_numOfScore; }
	// set score
	void setNumOfScore(int numOfScore);
	// check if player have tool
	bool haveTool(Tool::ToolType toolType) const;
	bool haveTool(Tool* tool) const;
	// change tool
	void changeTool(const std::shared_ptr<Tool>& tool);
	// get current tool
	std::shared_ptr<Tool> getCurrTool() const { return m_currTool; }
	// set life
	virtual void setNumOfLife(int numOfLife) override;
	// event when direction changed
	virtual void onDirectionChanged() override;
	// use current tool if can
	void useCurrTool();
	// event on update tool
	virtual void onToolUpdated(Tool* tool) override;
	// convert to string
	virtual string toString() const override;
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) override { obj->onCollide(this); }
	virtual void onCollide(Player* player) override { }
	virtual void onCollide(Shark* shark) override {} // TODO use this
	virtual void onCollide(Crab* crab) override {} // TODO use this
	virtual void onCollide(Rubber* rubber) override {} // TODO use this
	virtual void onCollide(Chest* chest) override; 
	virtual void onCollide(Wall* wall) override {} // TODO use this
	virtual void onCollide(Flow* flow) override;
	virtual void onCollide(Bullet* bullet) override {} // TODO use this
	virtual void onCollide(MachineGun* machineGun) override {}; // TODO use this
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
private:
	// swim animation frequency
	static const int SWIM_ANIM_FREQUENCY = 30;
	// stand animation frequency
	static const int STAND_ANIM_FREQUENCY = 100;
	// players default accelration
	static const float PLAYER_ACCELRATION;
	// default number of life
	static const int DEFAULT_LIFE = 6;
	// my tools
	std::vector<std::shared_ptr<Tool>> m_tools;
	// current tool
	std::shared_ptr<Tool> m_currTool;
	// score
	int m_numOfScore;
	// init
	void init();
};
