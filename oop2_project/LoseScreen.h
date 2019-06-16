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
 * LoseScreen class
 */
class LoseScreen :
	public GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>
{
public:
	// constructor
	explicit LoseScreen(sf::RenderWindow& window);
	// get back to menu button
	const std::shared_ptr<GUI::Button>& getBackToMenuBT() const { return m_backToMenuBT; }
	// get restart button
	const std::shared_ptr<GUI::Button>& getRestartBT() const { return m_restartLevelBT; }
	// convert to string
	virtual string toString() const override { return "LoseScreen: { " + BaseClass::toString() + " }"; }
private:
	// base class
	using BaseClass = GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>;
	// title
	std::shared_ptr<GUI::TextView> m_title;
	// image
	std::shared_ptr<GUI::ImageView> m_image;
	// restart level button
	std::shared_ptr<GUI::Button> m_backToMenuBT;
	// back to menu
	std::shared_ptr<GUI::Button> m_restartLevelBT;
	// init components
	void initComponents();
};

