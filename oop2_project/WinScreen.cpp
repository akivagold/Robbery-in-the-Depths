#include "WinScreen.h"

WinScreen::WinScreen(sf::RenderWindow & window, int score)
	: BaseClass(window)
{
	initComponents(score);
}

void WinScreen::initComponents(int score)
{
	// init title
	m_title = std::make_shared<GUI::TextView>(getWindow(), "You Win!");
	m_title->setTextColor(sf::Color(58, 122, 19));
	m_title->setTextSize(50);
	m_title->setFont("ARLRDBD");
	m_title->setTextStyle(sf::Text::Style::Bold);
	addView(m_title, sf::FloatRect(0.f, 0.f, 1.f, 0.2f));

	// init score
	m_score = std::make_shared<GUI::TextView>(getWindow(), "Your score is " + std::to_string(score));
	m_score->setTextColor(sf::Color(255, 209, 26));
	m_score->setTextSize(50);
	m_score->setFont("ARLRDBD");
	m_score->setTextStyle(sf::Text::Style::Bold);
	addView(m_score, sf::FloatRect(0.f, 0.18f, 1.f, 0.2f));

	// init image
	m_image = std::make_shared<GUI::ImageView>(getWindow());
	m_image->getImage().setTexture("win");
	//m_image->getImage().updateBounds(sf::FloatRect(0.f, 0.f, 0.3f, 0.2f));
	addView(m_image, sf::FloatRect(0.35f, 0.45f, 0.3f, 0.2f));
	
	// init back button
	m_backToMenuBT = std::make_shared<GUI::Button>(getWindow(), "Back To Menu");
	m_backToMenuBT->setButtonColor(sf::Color(230, 184, 0));
	m_backToMenuBT->setTextSize(30);
	m_backToMenuBT->setTextColor(sf::Color::White);
	m_backToMenuBT->setTextHAlignment(GUI::TextView::TextHAlignment::CENTER);
	addView(m_backToMenuBT, sf::FloatRect(0.37f, 0.75f, 0.27f, 0.2f));
}
