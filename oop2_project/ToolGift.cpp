#include "ToolGift.h"
#include "Player.h"

ToolGift::ToolGift(Tool::ToolType toolType)
	: Gift()
{
	setToolType(toolType);
}

void ToolGift::setToolType(Tool::ToolType toolType)
{
	m_toolType = toolType;
}

void ToolGift::takeSurprise(Player* owner)
{
	if (!owner->haveTool(m_toolType))
		owner->addTool(Tool::createTool(m_toolType, owner));

	// TODO need add ammo if have
}

string ToolGift::toString() const
{
	return "ToolGift: { toolTypeNum=" + std::to_string(m_toolType) + ", " + Gift::toString() + " }";
}
