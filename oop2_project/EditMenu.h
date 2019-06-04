#pragma once
//---- include section ------
#include "HorizontalLayout.h"
#include "Button.h"
#include "Cell.h"
#include <string>

//---- using section --------
using std::string;

/*
 * EditMenu class
 */
class EditMenu :
	public GUI::HorizontalLayout<GUI::View>
{
public:
	// base class
	using BaseClass = GUI::HorizontalLayout<GUI::View>;
	// constructor
	explicit EditMenu(sf::RenderWindow& window);
	// get add button
	const std::shared_ptr<GUI::Button>& getAddButton() const { return m_addButton; }
	// get delete button
	const std::shared_ptr<GUI::Button>& getDeleteButton() const { return m_deleteBt; }
	// get save button
	const std::shared_ptr<GUI::Button>& getSaveButton() const { return m_saveBt; }
	// get exit button
	const std::shared_ptr<GUI::Button>& getExitButton() const { return m_exitBt; }
	// set current cell
	void setCurrentCell(const GUI::Cell& cell);
	// convert to string
	virtual string toString() const override;
private:
	// buttons
	std::shared_ptr<GUI::Button> m_addButton, m_deleteBt, m_saveBt, m_exitBt;
	// current cell info text view
	std::shared_ptr<GUI::TextView> m_currCellTv;
	// init components
	void initComponents();
};

