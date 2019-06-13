#pragma once
//---- include section ------
#include <string>
#include <vector>
#include "ImageView.h"
#include "GameObjectInfo.h"

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
	explicit MapCellView(sf::RenderWindow& window);
	// get char
	char getChar() const { return m_ch; }
	// set char
	void setChar(const std::vector<GameObjectInfo>& gois, char ch);
	// convert to string
	virtual string toString() const override;
private:
	// char
	char m_ch;
	// update image by char
	void updateImage(const std::vector<GameObjectInfo>& gois, char ch);
};
