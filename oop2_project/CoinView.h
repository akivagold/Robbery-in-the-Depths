#pragma once
//---- include section ------
#include "View.h"
#include "ImageButton.h"
#include "ImageView.h"

/*
 * CoinView class
 */
class CoinView
	: public GUI::ImageButton
{
public:
	// constructor
	explicit CoinView(sf::RenderWindow& window, int numOfCoins = 0);
	// set num of coins
	void setNumOfCoins(int numOfCoins);
	// get num of life
	int getNumOfCoins() const { return m_numOfCoins; }
	// convert to string
	virtual string toString() const override;
private:
	// num of Coins
	int m_numOfCoins;
	// check if num  of life is legal
	void checkLegalCoinNum(int numOfCoins) const;
	// init
	void init();
};

