#include "ToolGift.h"
#include "Player.h"

string ToolGift::getToolName(Tool::ToolType toolType)
{
	string toolName;
	switch (toolType)
	{
		case Tool::TT_AK47: {
			toolName = "AK47";
		} break;
		case Tool::TT_GRENADE_LAUNCHER: {
			toolName = "Granade Launcher";
		} break;
		default: {
			throw std::invalid_argument("Cannot find tool name for the tool type " + std::to_string(toolType));
		} break;
	}
	return toolName;
}

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
	if (owner->haveTool(m_toolType)) {
		auto& tool = owner->getTool(m_toolType);
		if (!tool->isUseInfLimit())
			tool->appendUseLimit(tool->getDefUseLimit());
	}
	else {
		owner->addTool(Tool::createTool(m_toolType, owner));
	}
}

string ToolGift::toString() const
{
	return "ToolGift: { toolTypeNum=" + std::to_string(m_toolType) + ", " + Gift::toString() + " }";
}
