#pragma once
//---- include section ------
#include <string>
#include "Character.h"
#include "Tool.h"
#include "StopWatch.h"

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
	void appendScore(int numOfScore);
	// check if player have tool
	bool haveTool(Tool::ToolType toolType) const;
	bool haveTool(Tool* tool) const;
	// change tool
	void changeTool(const std::shared_ptr<Tool>& tool);
	// get current tool
	std::shared_ptr<Tool> getCurrTool() const { return m_currTool; }
	// set life
	virtual void setNumOfLife(int numOfLife) override;
	// use current tool if can
	void useCurrTool();
	// event on update tool
	virtual void onToolUpdated(Tool* tool) override;
	// decrease life
	virtual void decreaseLife(int numOfLife);
	// set on die listener
	void setOnDieListener(std::function<void()> dieListener) { m_dieHandler = dieListener; }
	// set on vanish listener
	void setOnVanishListener(std::function<void()> vanishListener) { m_vanishHandler = vanishListener; }
	// convert to string
	virtual string toString() const override;
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) override { obj->onCollide(this); }
	virtual void onCollide(Player* player) override {}
	virtual void onCollide(Shark* shark) override;
	virtual void onCollide(Crab* crab) override;
	virtual void onCollide(Rubber* rubber) override {} // TODO use this
	virtual void onCollide(Chest* chest) override; 
	virtual void onCollide(Wall* wall) override {} // TODO use this
	virtual void onCollide(Flow* flow) override;
	virtual void onCollide(Bullet* bullet) override;
	virtual void onCollide(MachineGun* machineGun) override {} // TODO use this
	virtual void onCollide(Grenade* grenade) override;
	virtual void onCollide(Explosion* explosion) override;
	virtual void onCollide(Box* box) override {}  // TODO use this
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
	// event when direction changed
	virtual void onDirectionChanged() override;
	// event on die
	virtual void onDie() override;
	// event on vanish
	virtual void onVanish() override;
private:
	// swim animation frequency
	static const int SWIM_ANIM_FREQUENCY = 30;
	// stand animation frequency
	static const int STAND_ANIM_FREQUENCY = 100;
	// players default accelration
	static const float PLAYER_ACCELRATION;
	// default number of life
	static const int DEFAULT_LIFE = 20;
	// time to recover
	static const int RECOVERY_TIME = 1000;
	// my tools
	std::vector<std::shared_ptr<Tool>> m_tools;
	// current tool
	std::shared_ptr<Tool> m_currTool;
	// score
	int m_numOfScore;
	// recover stopWatch
	StopWatch m_recoveSW;
	// recover flag
	bool m_isRecover;
	// die & vanish event handlers
	std::function<void()> m_dieHandler, m_vanishHandler;
	// init
	void init();
	// check if player is recover
	bool isRecover() const { return m_isRecover; }
	// switch current tool to next tool at list
	void switchToNextTool();
	// find tool index
	int findToolIndex(const std::shared_ptr<Tool>& tool);
	// start recover
	void recover();
	// register flag in BOFactory
	static bool isRegistered;
};
