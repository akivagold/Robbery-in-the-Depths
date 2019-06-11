#pragma once
//---- include section ------
#include <string>
#include "BaseScreen.h"
#include "RelativeLayout.h"
#include "Button.h"
#include "VerticalLayout.h"
#include "LevelFileManager.h"

//---- using section --------
using std::string;

/*
 * ChooseLevelScreen class
 */
class ChooseLevelScreen :
	public GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>
{
public:
	// base class
	using BaseClass = GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>;
	// constructor
	explicit ChooseLevelScreen(sf::RenderWindow& window, const LevelFileManager& lfm);
	// add level button click listener
	void addLevelBtClickListener(std::function<void(const std::shared_ptr<GUI::Button>&)> onLevelBtClicked);
	// convert to string
	virtual string toString() const override;
private:
	using LevelsLayout = std::shared_ptr<GUI::VerticalLayout<GUI::Button>>;
	// title
	std::shared_ptr<GUI::TextView> m_title;
	// buttons layout
	LevelsLayout m_levelsBtsLayout;
	// levels buttons
	std::vector<std::shared_ptr<GUI::Button>> m_levelsBts;
	// init components
	void initComponents(const LevelFileManager& lfm);
};

