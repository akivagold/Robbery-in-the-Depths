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
	static const int NUM_OF_TOOLS = 2;
	// tool type
	enum ToolType { TT_AK47, TT_GRENADE_LAUNCHER };
	// random tool type
	static ToolType randToolType();
	// create new tool by tool type
	static std::shared_ptr<Tool> createTool(ToolType toolType, Character* owner);
	// use tool
	virtual void useTool();
	// check if can use tool
	virtual bool canUsingTool() const { return (isUseInfLimit() || m_useLimit > 0); }
	// get tool type
	virtual ToolType getToolType() const = 0;
	// get my owner
	Character* getMyOwner() { return m_owner; }
	// get tool name
	virtual string getToolName() const = 0;
	// append use limit
	void appendUseLimit(int useLimitCount) { setUseLimit(getUseLimit() + useLimitCount); }
	// set use limit
	void setUseLimit(int useLimitCount);
	// get use limit
	int getUseLimit() const;
	// set infinity limit
	void setInfLimit();
	// get default use limit
	virtual int getDefUseLimit() const = 0;
	// check if using infinity limit
	bool isUseInfLimit() const { return m_withInfLlimit; }
	// convert to string
	virtual string toString() const;
protected:
	// constructor
	explicit Tool(Character* object, string toolName = "");
private:
	// owner of tool
	Character* m_owner;
	// using limit count
	int m_useLimit;
	// flag for infinity limit
	bool m_withInfLlimit;
	// update change to owner
	void updateOwner();
};
