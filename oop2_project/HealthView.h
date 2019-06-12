#pragma once
//---- include section ------
#include <string>
#include "HorizontalLayout.h"

//---- using section --------
using std::string;

/*
 * HealthView class
 */
class HealthView
	: public GUI::HorizontalLayout<GUI::View>
{
public:
	// convert to string
	virtual string toString() const override { return "HealthView: {" + HorizontalLayout::toString() + "}"; }
private:
	// constructor
	explicit HealthView(sf::RenderWindow& window);
	std::shared_ptr<View> m_barFullPart, m_barEmptyPart;
	void init();
};


