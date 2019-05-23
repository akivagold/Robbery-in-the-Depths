#pragma once
//---- include section ------
#include "View.h"
#include "HorizontalLayout.h"
#include "ImageView.h"

/*
 * LifeView class
 */
class LifeView
	: public GUI::HorizontalLayout<GUI::ImageView>
{
public:
	// constructor
	LifeView(sf::RenderWindow& window, int numOfLife = 0);
	//set life
	void setLife(int numOflife);
	// set num of life
	void setNumOfLife(int numOfLife);
	// get num of life
	int getNumOfLife() { return m_numOfLife; }
	// convert to string
	virtual string toString() const override;
private:
	//num of life
	int m_numOfLife;
	// crate life image
	std::shared_ptr<GUI::ImageView> crateLifeImage();
	// check if num  of life is legal
	void checkLegalLife(int numOfLife) const;
	// init
	void init();
};

