#pragma once
//---- include section ------
#include <string>
#include "TextView.h"

//---- using section --------
using std::string;
using sf::Text;

namespace GUI {
/*
 * Button class
 */
class Button :
	public TextView
{
public:
	// constructor
	explicit Button(sf::RenderWindow& window, const string& text = "");
	// set button background color
	void setButtonColor(const sf::Color& color) { m_btColor = color; }
	// get button background color
	const sf::Color& getButtonColor() const { return m_btColor; }
	// set selected button background color
	void setSelectedButtonColor(const sf::Color& color) { m_selectedBtColor = color; }
	// get selected button background color
	const sf::Color& getSelectedButtonColor() const { return m_selectedBtColor; }
	// set disable button background color
	void setDisableButtonColor(const sf::Color& color) { m_disabledBtColor = color; }
	// get disable button background color
	const sf::Color& getDisableButtonColor() const { return m_disabledBtColor; }
	// enable
	virtual void enable() override;
	// disable
	virtual void disable() override;
	// convert to string
	virtual string toString() const override;
private:
	// init components
	void initComponents();
	// button colors
	sf::Color m_disabledBtColor, m_btColor, m_selectedBtColor;
};
}
