#pragma once
//---- include section ------
#include <string>
#include "BaseScreen.h"
#include "RelativeLayout.h"
#include "GameMenu.h"
#include "World.h"
#include "GameAnimText.h"

//---- using section --------
using std::string;

/*
 * GameScreen class
 */
class GameScreen
	: public GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>
{
	
public:
	// constructor
	GameScreen(sf::RenderWindow& window);
	// get world
	World& getWorld() { return *m_world; }
	const World& getWorld() const { return *m_world; }
	// load level
	void loadLevel(const LevelInfo& levelInfo);
	// get game anim text
	const std::shared_ptr<GameAnimText>& getGameAnimText() const { return m_gameAnimText; }
	// get game screen
	const std::shared_ptr<GameMenu>& getGameMenu() const { return m_gameMenu; }
	// convert to string
	virtual string toString() const override;
private:
	// base class
	using BaseClass = GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>;
	// world
	std::shared_ptr<World> m_world;
	// game menu ptr
	std::shared_ptr<GameMenu> m_gameMenu;
	// game anim text
	std::shared_ptr<GameAnimText> m_gameAnimText;
	// init
	void init();
};


