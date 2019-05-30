#pragma once
//---- include section ------
#include <string>
#include "BoardObject.h"

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
	virtual bool canUsingTool() = 0;
	//get my owner
	const std::shared_ptr<BoardObject>& getMyowner() const { return m_owner; }
	// get tool name
	string getToolName() { return m_toolName; }
	// set tool name
	void setToolName(string toolName) { m_toolName = toolName; }
	//convert to string
	virtual string toString() const;
protected:
	// constructor
	explicit Tool(std::shared_ptr<BoardObject>& object, string toolName = " ");
private:
	// owner of tool
	std::shared_ptr<BoardObject> m_owner;
	// tool name
	string m_toolName;
};


