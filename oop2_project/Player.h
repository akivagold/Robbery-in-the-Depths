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
	// char
	static const char CHAR = 'p';
	// constructor
	explicit Player(GameScreen& gameScreen, int numOfLife = 0);
	// add new tool
	void addTool(std::shared_ptr<Tool> tool) { m_tools.push_back(tool); }
	// get number of tools
	int getNumOfTool() const { return int(m_tools.size()) - 1; }
	// get score
	int getScore() const { return m_score; }
	// change tool
	void changeTool(const std::shared_ptr<Tool>& tool);
	// get current tool
	std::shared_ptr<Tool> getCurrTool() const { return m_currTool; }
	// set life
	virtual void setNumOfLife(int numOfLife) override;
	// event when direction changed
	virtual void onDirectionChanged() override;
	// convert to string
	virtual string toString() const override;
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
private:
	// draw priority
	static const int DRAW_PRIORITY = 100;
	// swim animation frequency
	static const int SWIM_ANIM_FREQUENCY = 30;
	// stand animation frequency
	static const int STAND_ANIM_FREQUENCY = 100;
	// my tools
	std::vector<std::shared_ptr<Tool>> m_tools;
	// current tool
	std::shared_ptr<Tool> m_currTool;
	// score
	int m_score;
	// init
	void init();
};


