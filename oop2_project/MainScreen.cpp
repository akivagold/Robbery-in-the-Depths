#include "MainScreen.h"

MainScreen::MainScreen(sf::RenderWindow& window) 
	: BaseScreen(window),
	m_titleTV(std::make_shared<GUI::TextView>(window, "Robbery in the Depths")),
	m_startBt(std::make_shared<GUI::Button>(window, "Start Game")),
	m_editBt(std::make_shared<GUI::Button>(window, "Edit Level")),
	m_exitBt(std::make_shared<GUI::Button>(window, "Exit"))
{
	initComponents();
}

string MainScreen::toString() const
{
	return "MainScreen: { " + BaseScreen::toString() + " }";
}

void MainScreen::initComponents()
{
	getBackground().setTexture("main_background");

	// init title
	m_titleTV->setFont("segoeprb");
	m_titleTV->setTextColor(sf::Color(132, 60, 12));
	m_titleTV->setTextSize(60);
	addView(m_titleTV, sf::FloatRect(0.f, 0.f, 1.f, 0.3f));

	// init start button
	m_startBt->setButtonColor(sf::Color(0, 176, 80));
	m_startBt->setSelectedButtonColor(sf::Color(0, 96, 43));
	m_startBt->setTextColor(sf::Color::White);
	m_startBt->setTextSize(25);
	addView(m_startBt, sf::FloatRect(1.f/3.f, 0.4f, 1.f/3.f, 0.1f));

	// init edit button
	m_editBt->setButtonColor(sf::Color(255, 192, 0));
	m_editBt->setSelectedButtonColor(sf::Color(172, 131, 0));
	m_editBt->setTextColor(sf::Color::White);
	m_editBt->setTextSize(25);
	addView(m_editBt, sf::FloatRect(1.f / 3.f, 0.57f, 1.f / 3.f, 0.1f));

	// init exit button
	m_exitBt->setButtonColor(sf::Color(255, 0, 0));
	m_exitBt->setSelectedButtonColor(sf::Color(162, 0, 0));
	m_exitBt->setTextColor(sf::Color::White);
	m_exitBt->setTextSize(25);
	addView(m_exitBt, sf::FloatRect(1.f / 3.f, 0.74f, 1.f / 3.f, 0.1f));
}
