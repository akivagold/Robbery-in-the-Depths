#include "LoseScreen.h"


LoseScreen::LoseScreen(sf::RenderWindow& window)
	: BaseClass(window)
{
	initComponents();
}

void LoseScreen::initComponents()
{
	// init title
	m_title = std::make_shared<GUI::TextView>(getWindow(), "You Lose!");
	m_title->setTextColor(sf::Color::Red);
	m_title->setTextSize(50);
	m_title->setFont("ARLRDBD");
	m_title->setTextStyle(sf::Text::Style::Bold);
	addView(m_title, sf::FloatRect(0.f, 0.f, 1.f, 0.2f));

	// init image
	m_image = std::make_shared<GUI::ImageView>(getWindow());
	m_image->getImage().setTexture("lose");
	addView(m_image, sf::FloatRect(0.35f, 0.2f, 0.32f, 0.32f));

	// init restart button
	m_restartLevelBT = std::make_shared<GUI::Button>(getWindow(), "Restart Level");
	m_restartLevelBT->setButtonColor(sf::Color(51, 204, 51));
	m_restartLevelBT->setTextSize(40);
	m_restartLevelBT->setTextColor(sf::Color::White);
	addView(m_restartLevelBT, sf::FloatRect(0.37f, 0.58f, 0.27f, 0.15f));
	
	// init back button
	m_backToMenuBT = std::make_shared<GUI::Button>(getWindow(), "Back To Menu");
	m_backToMenuBT->setButtonColor(sf::Color(230, 184, 0));
	m_backToMenuBT->setTextSize(40);
	m_backToMenuBT->setTextColor(sf::Color::White);
	addView(m_backToMenuBT, sf::FloatRect(0.37f, 0.78f, 0.27f, 0.15f));
}
