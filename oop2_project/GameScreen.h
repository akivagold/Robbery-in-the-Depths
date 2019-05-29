#pragma once
//---- include section ------
#include <string>
#include "BaseScreen.h"
#include "RelativeLayout.h"
#include "GameMenu.h"
#include "World.h"

//---- using section --------
using std::string;

/*
 * GameScreen class
 */
class GameScreen
	: public GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>
{
	
public:
	// base class
	using BaseClass = GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>;
	// constructor
	GameScreen(sf::RenderWindow& window);
	// get world
	World& getWorld() { return *m_world; }
	const World& getWorld() const { return *m_world; }
	// get game screen
	const std::shared_ptr<GameMenu>& getGameMenu() const { return m_gameMenu; }
	// convert to string
	virtual string toString() const override;
private:
	// world
	std::shared_ptr<World> m_world;
	// game menu ptr
	std::shared_ptr<GameMenu> m_gameMenu;
	// init
	void init();
};


