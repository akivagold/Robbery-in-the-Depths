#pragma once
//---- include section ------
#include <string>
#include "BaseScreen.h"
#include "RelativeLayout.h"
#include "Button.h"
#include "VerticalLayout.h"
#include "ImageView.h"

//---- using section --------
using std::string;

/*
 * WinScreen class
 */
class WinScreen :
	public GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>
{
public:
	// base class
	using BaseClass = GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>;
	// constructor
	explicit WinScreen(sf::RenderWindow& window, int score);
	// convert to string
	virtual string toString() const override { return "WinScreen: { " + BaseClass::toString() + " }"; }
private:
	// title
	std::shared_ptr<GUI::TextView> m_title;
	// score
	std::shared_ptr<GUI::TextView> m_score;
	// image
	std::shared_ptr<GUI::ImageView> m_image;
	// levels buttons
	std::shared_ptr<GUI::Button> m_backToMenuBT;
	// init components
	void initComponents(int score);
};

