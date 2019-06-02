#pragma once
//---- include section ------
#include "VerticalLayout.h"
#include "HorizontalLayout.h"
#include "TableLayout.h"
#include "Matrix.h"
#include <exception>
#include <string>

//---- using section --------
using std::string;

namespace GUI {
/*
 * TableLayout class
 */
template <class ViewType = GUI::View>
class TableLayout :
	public GUI::VerticalLayout<HorizontalLayout<ViewType>>
{
public:
	// define base class
	using BaseClass = VerticalLayout<HorizontalLayout<ViewType>>;
	// constructor
	explicit TableLayout(sf::RenderWindow& window, const sf::Vector2i& size = { 0, 0 }) : BaseClass(window)  { resize(size); }
	// resize table
	void resize(int numOfRows, int numOfCols) { resize({ numOfRows, numOfCols }); }
	void resize(const sf::Vector2i& size);
	// clear table
	void clear() { this->removeAllViews(); }
	// get number of rowss
	int getNumOfRows() const { return m_size.x; }
	// get number of columns
	int getNumOfCols() const { return m_size.y; }
	// get size
	const sf::Vector2i& getSize() const { return m_size; }
	// get view at position
	const std::shared_ptr<ViewType>& getViewAt(const Cell& cell) const;
	// for each all cells
	void forEach(std::function<void(const Cell&, const std::shared_ptr<ViewType>&)> onGetCellData);
	// convert to string
	virtual string toString() const override;


	// TODO add operators

private:
	// size of table
	sf::Vector2i m_size;
	// check if is legal cell
	bool isLegalCell(const Cell& cell) const;
	// disable parent functions
	using BaseClass::addView;
	using BaseClass::getView;
	using BaseClass::removeView;
	using BaseClass::getChildRelativeHeight;
};

template<class ViewType>
void TableLayout<ViewType>::resize(const sf::Vector2i& size)
{
	// clear last views
	clear();

	// create table
	m_size = size;
	for (size_t rowNum = 0; rowNum < getNumOfRows(); ++rowNum) {
		// create row
		auto rowLayout = std::make_shared<HorizontalLayout<ViewType>>(this->getWindow());
		for (size_t colNum = 0; colNum < getNumOfCols(); ++colNum) {
			// create cell view
			auto cellView = std::make_shared<ViewType>(this->getWindow());
			// init cell view
			cellView->getBorder().setColor(sf::Color(140, 140, 140));
			cellView->getBorder().setSize(0.5f);

			rowLayout->addView(cellView);
		}
		addView(rowLayout);
	}
}

template<class ViewType>
const std::shared_ptr<ViewType>& TableLayout<ViewType>::getViewAt(const Cell& cell) const
{
	// check legal cell
	if(!isLegalCell(cell))
		throw std::out_of_range("The cell: " + cell.toString() + " doesn't exists in table");
	return getView(cell.getRowNum())->getView(cell.getColNum());
}

template<class ViewType>
void TableLayout<ViewType>::forEach(std::function<void(const Cell&, const std::shared_ptr<ViewType>&)> onGetCellData)
{
	for (size_t rowNum = 0; rowNum < getNumOfRows(); ++rowNum) {
		for (size_t colNum = 0; colNum < getNumOfCols(); ++colNum) {
			Cell cell(static_cast<int>(rowNum), static_cast<int>(colNum));
			onGetCellData(cell, getViewAt(cell));
		}
	}
}

template<class ViewType>
string TableLayout<ViewType>::toString() const
{
	return "TableLayout: { " + BaseClass::toString() + " }";
}

template<class ViewType>
bool TableLayout<ViewType>::isLegalCell(const Cell& cell) const
{
	return ((cell.getRowNum() < m_size.x)&&(cell.getColNum() < m_size.y));
}
}
