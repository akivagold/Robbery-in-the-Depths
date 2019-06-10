#pragma once
//---- include section ------
#include <string>
#include "MainScreen.h"
#include "EditScreen.h"
#include "GameScreen.h"
#include "LevelInfo.h"
#include "LevelFileManager.h"
#include "ChooseLevelScreen.h"

//---- using section --------
using std::string;

/*
 * GameController class
 */
class GameController
{
public:
	// constructor
	GameController() = default;
	// run
	void run();
	// convert to string
	virtual string toString() const;
private:
	// run main screen
	void runMainScreen(sf::RenderWindow& window);
	// run choose level screen
	void runChooseLevelScreen(sf::RenderWindow& window, LevelFileManager& lfm, std::function<void(const LevelInfo&)> onLevelChoosed);
	// run game screen
	void runGameScreen(sf::RenderWindow& window, const LevelInfo& levelInfo);
	// run edit screen
	void runEditScreen(sf::RenderWindow& window, LevelFileManager& levelFileManager, const LevelInfo& levelInfo);
};
