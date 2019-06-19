#include "LoseScreen.h"
#include "SoundManager.h"

LoseScreen::LoseScreen(sf::RenderWindow& window)
	: BaseClass(window)
{
	initComponents();
}

void LoseScreen::initComponents()
{
	GUI::SoundManager::getInterface().playBackgroundMusic("lose");

	// init title
	m_title = std::make_shared<GUI::TextView>(getWindow(), "You Lose!");
	m_title->setTextColor(sf::Color::Red);
	m_title->setTextSize(55);
	m_title->setFont("segoeprb");
	m_title->setTextStyle(sf::Text::Style::Bold);
	addView(m_title, sf::FloatRect(0.f, 0.f, 1.f, 0.2f));

	// init image
	m_animView = std::make_shared<GUI::AnimationView>(getWindow());
	m_animView->setAnimation("cry");
	m_animView->setAnimationFrequency(30);
	addView(m_animView, sf::FloatRect(0.35f, 0.2f, 0.32f, 0.43f));

	// init restart button
	m_restartLevelBT = std::make_shared<GUI::Button>(getWindow(), "Restart Level");
	m_restartLevelBT->setButtonColor(sf::Color(63, 200, 63));
	m_restartLevelBT->setSelectedButtonColor(sf::Color(34, 126, 34));
	m_restartLevelBT->setTextSize(40);
	m_restartLevelBT->setTextColor(sf::Color::White);
	addView(m_restartLevelBT, sf::FloatRect(0.37f, 0.72f, 0.27f, 0.1f));
	
	// init back button
	m_backToMenuBT = std::make_shared<GUI::Button>(getWindow(), "Back To Menu");
	m_backToMenuBT->setButtonColor(sf::Color(230, 184, 0));
	m_backToMenuBT->setSelectedButtonColor(sf::Color(114, 115, 0));
	m_backToMenuBT->setTextSize(40);
	m_backToMenuBT->setTextColor(sf::Color::White);
	addView(m_backToMenuBT, sf::FloatRect(0.37f, 0.85f, 0.27f, 0.1f));
}
