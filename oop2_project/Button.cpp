//---- include section ------
#include "Button.h"
#include "SoundManager.h"

GUI::Button::Button(sf::RenderWindow& window, const string& text)
	: TextView(window, text), m_disabledBtColor(197, 197, 197), m_btColor(96, 61, 255), m_selectedBtColor(30, 58, 244)
{
	initComponents();
}

void GUI::Button::enable()
{
	TextView::enable();
	getBackground().setColor(m_btColor);
}

void GUI::Button::disable()
{
	TextView::disable();
	getBackground().setColor(m_disabledBtColor);
}

string GUI::Button::toString() const
{
	return "Button: { " + TextView::toString() + " }";
}

void GUI::Button::initComponents()
{
	setFont("CURLZ");
	setTextStyle(sf::Text::Style::Bold);
	getBorder().setSize(1.f);
	getBorder().setColor(sf::Color::Black);
	getBackground().setColor(m_btColor);

	// init sounds at events
	addEnterListener([this](View &view) {
		SoundManager::getInterface().playSound("bt_hover");
		view.getBackground().setColor(m_selectedBtColor);
	});
	addClickListener([](View &view) {
		SoundManager::getInterface().playSound("bt_click");
	});
	addLeaveListener([this](View &view) {
		view.getBackground().setColor(m_btColor);
	});
}
