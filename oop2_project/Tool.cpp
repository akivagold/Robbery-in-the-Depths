#include "Tool.h"


Tool::Tool(std::shared_ptr<BoardObject>& object, string toolName)
	: m_owner(object)
{}

string Tool::toString() const
{
	return "Tool: { MyOwner: " + m_owner->toString() + " } ";
}