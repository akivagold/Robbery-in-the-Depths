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
	// convert to string
	virtual string toString() const override;
protected:
	// choose what to do
	virtual void playChoice() override;
private:
	// my tools
	std::vector<std::shared_ptr<Tool>> m_tools;
	// current tool
	std::shared_ptr<Tool> m_currTool;
	// score
	int m_score;
	// init
	void init();
};


