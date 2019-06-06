#include "EditMenu.h"

EditMenu::EditMenu(sf::RenderWindow& window)
	: BaseClass(window)
{
	initComponents();
}

void EditMenu::setCurrentCell(const GUI::Cell& cell)
{
	m_currCellTv->setText("Cell: " + std::to_string(cell.getRowNum()) + ", " + std::to_string(cell.getColNum()));
}

string EditMenu::toString() const
{
	return "EditMenu: { " + BaseClass::toString() + " }";
}

void EditMenu::initComponents()
{
	getBackground().setColor(sf::Color(255, 238, 179));
	getBorder().setSize(1);
	getBorder().setColor(sf::Color(75, 69, 49));

	// init delete button
	m_deleteBt = std::make_shared<GUI::Button>(getWindow(), "Delete");
	m_deleteBt->setButtonColor(sf::Color(204, 11, 63));
	m_deleteBt->setSelectedButtonColor(sf::Color(137, 20, 52));
	m_deleteBt->setTextSize(25);
	addView(m_deleteBt);

	// init current cell
	m_currCellTv = std::make_shared<GUI::TextView>(getWindow());
	m_currCellTv->setTextSize(27);
	m_currCellTv->setTextColor(sf::Color(40, 5, 83));
	m_currCellTv->setTextStyle(sf::Text::Style::Bold);
	m_currCellTv->setFont("ARLRDBD");
	addView(m_currCellTv);
	setCurrentCell(GUI::Cell(0, 0));

	// init save button
	m_saveBt = std::make_shared<GUI::Button>(getWindow(), "Save");
	m_saveBt->setButtonColor(sf::Color(120, 89, 255));
	m_saveBt->setSelectedButtonColor(sf::Color(74, 55, 154));
	m_saveBt->setTextSize(25);
	addView(m_saveBt);

	// init exit button
	m_exitBt = std::make_shared<GUI::Button>(getWindow(), "Exit");
	m_exitBt->setButtonColor(sf::Color(219, 0, 0));
	m_exitBt->setSelectedButtonColor(sf::Color(127, 5, 5));
	m_exitBt->setTextSize(25);
	addView(m_exitBt);
}
