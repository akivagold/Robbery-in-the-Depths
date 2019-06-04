#pragma once
//---- include section ------
#include <string>
#include "Character.h"


//---- using section --------
using std::string;

/*
 * Tool class
 */
class Tool
{
public:
	// use tool
	virtual void useTool() = 0;
	// check if can use tool
	virtual bool canUsingTool() const = 0;
	//get my owner
	Character* getMyOwner() { return m_owner; }
	// get tool name
	const string& getToolName() const { return m_toolName; }
	// set tool name
	void setToolName(const string& toolName) { m_toolName = toolName; }
	//convert to string
	virtual string toString() const;
protected:
	// constructor
	explicit Tool(Character* object, string toolName = " ");
private:
	// owner of tool
	Character* m_owner;
	// tool name
	string m_toolName;
};


