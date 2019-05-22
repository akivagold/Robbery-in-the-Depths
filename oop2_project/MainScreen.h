#pragma once
//---- include section ------
#include "BaseScreen.h"
#include "RelativeLayout.h"
#include "TextView.h"
#include "Button.h"


//---- using section --------
using std::string;

/*
 * MainScreen class
 */
class MainScreen : public GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>
{
public:
	// base class
	using BaseScreen = GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>;
	// constructor
	MainScreen(sf::RenderWindow& window);
	// get title text view
	const std::shared_ptr<GUI::TextView>& getTitleTV() const { return m_titleTV; }
	// get start button
	const std::shared_ptr<GUI::Button>& getStartBt() const { return m_startBt; }
	// get edit button
	const std::shared_ptr<GUI::Button>& getEditBt() const { return m_editBt; }
	// get exit button
	const std::shared_ptr<GUI::Button>& getExitBt() const { return m_exitBt; }
	// destructor
	virtual ~MainScreen() = default;
	// convert to string
	virtual string toString() const override;
private:
	// title text view
	std::shared_ptr<GUI::TextView> m_titleTV;
	// buttons
	std::shared_ptr<GUI::Button> m_startBt, m_editBt, m_exitBt;
	// init components
	void initComponents();
};

