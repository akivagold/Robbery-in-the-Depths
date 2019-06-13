#include "GameMenu.h"

GameMenu::GameMenu(sf::RenderWindow & window)
	:HorizontalLayout(window), 
	m_coinView(std::make_shared<CoinView>(window)),
	m_lifeView(std::make_shared<LifeView>(window)),
	m_toolView(std::make_shared<ToolView>(window)),
	m_levelNumTV(std::make_shared<GUI::TextView>(window))
{
	initComponents();
}

string GameMenu::toString() const
{
	return "GameMenu: { " + HorizontalLayout::toString() + " }";
}

void GameMenu::initComponents()
{
	getBackground().setColor(sf::Color(255, 240, 164));
	getBorder().setSize(2);
	getBorder().setColor(sf::Color::Black);
	addView(m_coinView, 0.1f);
	m_lifeView->setNumOfLife(3);
	addView(m_lifeView, 0.5f);
	m_levelNumTV->setText("Level num 1");
	m_levelNumTV->setTextSize(30);
	m_levelNumTV->setTextColor(sf::Color(27, 0, 87));
	m_levelNumTV->setFont("ARLRDBD");
	addView(m_levelNumTV, 0.3f);
	addView(m_toolView, 0.1f);
}
