//---- include section ------
#include "Cell.h"
#include <stdexcept>

GUI::Cell::Cell(int rowNum, int colNum)
{
	setCell(rowNum, colNum);
}

void GUI::Cell::setCell(int rowNum, int colNum)
{
	if (isValidCell(rowNum, colNum))
	{
		m_rowNum = rowNum;
		m_colNum = colNum;
	}
	else
		throw std::out_of_range("Illegal cell: rowNum = " + std::to_string(rowNum) + ", colNum = " + std::to_string(colNum));
}

void GUI::Cell::setRowNum(int rowNum)
{
	if (rowNum < 0)
		throw std::out_of_range("Ilegal row number =" + std::to_string(rowNum));
	m_rowNum = rowNum;
}

void GUI::Cell::setColNum(int colNum)
{
	if (colNum < 0)
		throw std::out_of_range("Ilegal column number =" + std::to_string(colNum));
	m_colNum = colNum;
}

bool GUI::Cell::isValidCell(int rowNum, int colNum)
{
	if ((rowNum < 0) || (colNum < 0))
		return false;
	return true;
}

string GUI::Cell::toString() const
{
	return "Cell: { rowNum=" + std::to_string(m_rowNum) + ", colNum=" + std::to_string(m_colNum) + " }";
}

GUI::Cell operator-(const GUI::Cell& cell1, const GUI::Cell& cell2) {
	return GUI::Cell(cell1.getRowNum() - cell2.getRowNum(), cell1.getColNum() - cell2.getColNum());
}