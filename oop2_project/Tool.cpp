#include "Tool.h"
#include "AK47.h"

Tool::Tool(Character* object, string toolName)
	: m_owner(object)
{}


Tool::ToolType Tool::randToolType()
{
	return static_cast<ToolType>(rand() % NUM_OF_TOOLS);
}

std::shared_ptr<Tool> Tool::createTool(ToolType toolType, Character* owner)
{
	std::shared_ptr<Tool> tool;

	switch (toolType)
	{
		case ToolType::TT_AK47: {
			tool = std::make_shared<AK47>(owner);
		} break;
		default:
			throw std::out_of_range("Cannot find the tool type=" + std::to_string(toolType));
		break;
	}

	return tool;
}

string Tool::toString() const
{
	return "Tool: { }"; // don't print owner!!
}