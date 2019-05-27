#include "GameScreen.h"

GameScreen::GameScreen(sf::RenderWindow& window)
	: BaseScreen(window), m_gameMenu(std::make_shared<GameMenu>(window))
{}

string GameScreen::toString() const
{
	return string();
}
