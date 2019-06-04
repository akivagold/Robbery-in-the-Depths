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
	// number of tools
	static const int NUM_OF_TOOLS = 1;
	// weapon type
	enum ToolType { TT_AK47 }; // TODO add more tools to here
	// random tool type
	static ToolType randToolType();
	// use tool
	virtual void useTool() = 0;
	// check if can use tool
	virtual bool canUsingTool() const = 0;
	// get tool type
	virtual ToolType getToolType() const = 0;
	// get my owner
	Character* getMyOwner() { return m_owner; }
	// get tool name
	const string& getToolName() const { return m_toolName; }
	// set tool name
	void setToolName(const string& toolName) { m_toolName = toolName; }
	// create new tool by tool type
	static std::shared_ptr<Tool> createTool(ToolType toolType, Character* owner);
	// convert to string
	virtual string toString() const;
protected:
	// constructor
	explicit Tool(Character* object, string toolName = "");
private:
	// owner of tool
	Character* m_owner;
	// tool name
	string m_toolName;
};


