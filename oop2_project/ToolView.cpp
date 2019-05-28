#include "ToolView.h"

ToolView::ToolView(sf::RenderWindow& window)
	: ImageButton(window)
{
	init();
}

void ToolView::setAmmo(int ammoQuntity)
{
	if (ammoQuntity < 0)
		throw std::out_of_range("Ammo Quntity " + std::to_string(ammoQuntity) + " is iilegel");
	m_ammo = ammoQuntity;
	setText(std::to_string(m_ammo));
}

string ToolView::toString() const 
{
	return "ToolView: { " + ImageButton::toString() + " } ";
}

void ToolView::init()
{
	getImage().setTexture("ak47");
	setAmmo(100);
	setTextHAligment(GUI::TextView::TextHAlignment::CENTER);
	setTextSize(30);
	getBorder().setSize(1);
	getBorder().setColor(sf::Color::Black);
}
