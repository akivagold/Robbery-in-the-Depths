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
	// set ammo
	void setAmmo(int ammQuntity);
	// set cuurent tool
	void setCurrTool(const std::shared_ptr<Tool>& currTool) { m_currTool = currTool; }
	// get cuurent tool
	const std::shared_ptr<Tool>& getCurrTool() const { return m_currTool; }
	// get ammo
	int getAmmo() const { return m_ammo; }
	// convert to string
	virtual string toString() const override; 
private:
	// current tool
	std::shared_ptr<Tool> m_currTool;
	// num Of ammo if have
	int m_ammo;
	// init
	void init();	
};


