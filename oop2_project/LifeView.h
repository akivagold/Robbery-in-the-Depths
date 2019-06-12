#pragma once
//---- include section ------
#include "View.h"
#include "HorizontalLayout.h"
#include "ImageView.h"
#include "Character.h"

/*
 * LifeView class
 */
class LifeView
	: public GUI::HorizontalLayout<GUI::ImageView>
{
public:
	// constructor
	explicit LifeView(sf::RenderWindow& window, int numOfLife = 0);
	// set life
	void setLife(int numOflife);
	// set num of life
	void setNumOfLife(int numOfLife);
	// get num of life
	int getNumOfLife() const { return m_numOfLife; }
	// convert to string
	virtual string toString() const override;
private:
	// num of life
	int m_numOfLife;
	// create life image
	std::shared_ptr<GUI::ImageView> createLifeImage();
	std::shared_ptr<GUI::ImageView> createLifeImage2();
	// check if num  of life is legal
	void checkLegalLife(int numOfLife) const;
	// init
	void init();
	std::shared_ptr<GUI::ImageView> m_barFullPart, m_barEmptyPart;
};
