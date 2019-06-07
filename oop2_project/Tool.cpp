#include "Tool.h"
#include "AK47.h"
#include "GrenadeLauncher.h"

Tool::Tool(Character* object, string toolName)
	: m_owner(object), m_withInfLlimit(false), m_useLimit(0)
{}

void Tool::updateOwner()
{
	m_owner->onToolUpdated(this);
}

Tool::ToolType Tool::randToolType()
{
	return static_cast<ToolType>(rand() % NUM_OF_TOOLS);
}

void Tool::useTool()
{
	if (!canUsingTool()) {
		throw std::logic_error("Cannot use tool without use limit");
	}
	if (!isUseInfLimit()) {
		m_useLimit--;
		updateOwner();
	}
}

std::shared_ptr<Tool> Tool::createTool(ToolType toolType, Character* owner)
{
	std::shared_ptr<Tool> tool;

	switch (toolType)
	{
		case ToolType::TT_AK47: {
			tool = std::make_shared<AK47>(owner);
		} break;
		case ToolType::TT_GRENADE_LAUNCHER: {
			tool = std::make_shared<GrenadeLauncher>(owner);
		} break;
		default:
			throw std::out_of_range("Cannot find the tool type=" + std::to_string(toolType));
		break;
	}

	return tool;
}

void Tool::setUseLimit(int useLimitCount)
{
	if (useLimitCount < 0)
		throw std::out_of_range("Use limit (=" + std::to_string(useLimitCount) + ") must be bigger or equals to zero");
	m_withInfLlimit = false;
	m_useLimit = useLimitCount;
	updateOwner();
}

int Tool::getUseLimit() const
{
	if (isUseInfLimit())
		throw std::logic_error("Cannot get use limit because is using infinity limit");
	return m_useLimit;
}

void Tool::setInfLimit()
{
	m_useLimit = 0;
	m_withInfLlimit = true;
	updateOwner();
}

string Tool::toString() const
{
	return "Tool: { useLimit=" + std::to_string(m_useLimit) + ", withInfLimit=" + std::to_string(m_withInfLlimit) + " }"; // don't print owner!!
}