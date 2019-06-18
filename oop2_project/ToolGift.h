#pragma once
//---- include section ------
#include "Gift.h"
#include "Tool.h"
#include <string>

//---- using section --------
using std::string;

/*
 * ToolGift class
 */
class ToolGift :
	public Gift
{
public:
	// random tool gift
	static std::shared_ptr<ToolGift> randToolGift() { return std::make_shared<ToolGift>(Tool::randToolType()); }
	// get tool name
	static string getToolName(Tool::ToolType toolType);
	// constructor
	explicit ToolGift(Tool::ToolType toolType);
	// set tool type
	void setToolType(Tool::ToolType toolType);
	// get info
	virtual string getInfo() const override { return getToolName(m_toolType); }
	// get tool type
	Tool::ToolType getToolType() const { return m_toolType; }
	// take surprise
	virtual void takeSurprise(Player* owner);
	// convert to string
	virtual string toString() const override;
private:
	// tool type
	Tool::ToolType m_toolType;
};
