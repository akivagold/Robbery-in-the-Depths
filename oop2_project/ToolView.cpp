#include "ToolView.h"

ToolView::ToolView(sf::RenderWindow& window)
	: ImageButton(window), m_currTool(nullptr)
{
	init();
}

void ToolView::setTool(const std::shared_ptr<Tool>& currTool)
{
	m_currTool = currTool;
	getImage().setTexture(currTool->getToolName());
	updateUseLimit();
}

void ToolView::updateUseLimit()
{
	if (m_currTool->isUseInfLimit())
		setText("");
	else
		setText(std::to_string(m_currTool->getUseLimit()));
}

void ToolView::clearTool()
{
	getImage().clear();
	setText("");
}

string ToolView::toString() const
{
	return "ToolView: { " + ImageButton::toString() + " } ";
}

void ToolView::init()
{
	setTextHAligment(GUI::TextView::TextHAlignment::CENTER);
	setTextSize(30);
	getBorder().setSize(1);
	getBorder().setColor(sf::Color::Black);
}