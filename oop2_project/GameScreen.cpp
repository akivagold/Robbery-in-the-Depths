#include "GameScreen.h"

GameScreen::GameScreen(sf::RenderWindow& window)
	: BaseScreen(window), m_gameMenu(std::make_shared<GameMenu>(window)), 
	  m_world(std::make_shared<World>(window))
{
	init();
}

void GameScreen::loadLevel(const LevelInfo& levelInfo)
{
	// TODO need clear game menu

	// play level music
	GUI::SoundManager::getInterface().playBackgroundMusic(levelInfo.getBackMusicName());
	// update level name
	getGameMenu()->getLevelNumTV()->setText(levelInfo.getName());
	// load world
	m_world->loadLevel(*this, levelInfo);

	m_gameAnimText->showText(GameAnimText::TextInfo("Start to play", sf::Color::Black));
}

string GameScreen::toString() const
{
	return "GameScreen: { " + m_world->toString() + ", " + BaseClass::toString() + " }";
}

void GameScreen::init()
{
	// remove backgroud
	getBackground().setColor(sf::Color::Transparent);
	// add world
	addBackRootView(m_world);
	// add game menu
	addView(m_gameMenu, sf::FloatRect(0.f, 0.f, 1.f, 0.2f));

	// add game animate text
	m_gameAnimText = std::make_shared<GameAnimText>(getWindow());
	addView(m_gameAnimText, sf::FloatRect(0.f, 0.08f, 1.f, 0.5));
}
