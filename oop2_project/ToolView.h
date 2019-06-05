#pragma once
//---- include section ------
#include <string>
#include "ImageButton.h"
#include "Tool.h"

//---- using section --------
using std::string;

/*
 * ToolView class
 */
class ToolView :
	public GUI::ImageButton
{

public:
	// constructor
	explicit ToolView(sf::RenderWindow& window);
	// set tool
	void setTool(const std::shared_ptr<Tool>& currTool);
	// check if have tool
	bool haveTool() const { return bool(m_currTool); }
	// update use limit
	void updateUseLimit();
	// clear tool
	void clearTool();
	// convert to string
	virtual string toString() const override; 
private:
	// current tool
	std::shared_ptr<Tool> m_currTool;
	// init
	void init();	
};
