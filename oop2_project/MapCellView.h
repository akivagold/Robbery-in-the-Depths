#pragma once
//---- include section ------
#include <string>
#include "ImageView.h"

//---- using section --------
using std::string;

/*
 * MapCellView class
 */
class MapCellView
	: public GUI::ImageView
{
public:
	// constructor
	explicit MapCellView(sf::RenderWindow& window, char ch = ' ');
	// get char
	char getChar() const { return m_ch; }
	// set char
	void setChar(char ch);
	// convert to string
	virtual string toString() const override;
private:
	// char
	char m_ch;
	// update image by char
	void updateImage(char ch);
};

