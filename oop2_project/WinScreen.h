#pragma once
//---- include section ------
#include <string>
#include "BaseScreen.h"
#include "RelativeLayout.h"
#include "Button.h"
#include "VerticalLayout.h"
#include "AnimationView.h"

//---- using section --------
using std::string;

/*
 * WinScreen class
 */
class WinScreen :
	public GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>
{
public:
	// constructor
	explicit WinScreen(sf::RenderWindow& window, int score);
	// get back to menu button
	const std::shared_ptr<GUI::Button>& getBackToMenuBT() const { return m_backToMenuBT; }
	// convert to string
	virtual string toString() const override { return "WinScreen: { " + BaseClass::toString() + " }"; }
private:
	// base class
	using BaseClass = GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>;
	// title
	std::shared_ptr<GUI::TextView> m_title;
	// score
	std::shared_ptr<GUI::TextView> m_score;
	// win animation
	std::shared_ptr<GUI::AnimationView> m_animView;
	// levels buttons
	std::shared_ptr<GUI::Button> m_backToMenuBT;
	// init components
	void initComponents(int score);
};

