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
	void setTool(Tool& tool);
	// set ammo
	void setAmmo(int ammQuntity);
	// set cuurent tool
	void setCurrTool(Tool& currTool) { m_currTool = currTool; }
	// get cuurent tool
	Tool& getCurrTool() { return m_currTool; }
	// get ammo
	int getAmmo() const { return m_ammo; }
	// convert to string
	virtual string toString() const override; 
private:
	// current tool
	Tool m_currTool;
	// num Of ammo
	int m_ammo;
	// init
	void init();
	
};


