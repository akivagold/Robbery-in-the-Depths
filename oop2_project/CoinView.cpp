#include "CoinView.h"


CoinView::CoinView(sf::RenderWindow & window, int numOfCoins)
	:ImageButton(window)
{
	init();
	setNumOfCoins(numOfCoins);
}

void CoinView::setNumOfCoins(int numOfCoins)
{
	checkLegalCoinNum(numOfCoins);
	m_numOfCoins = numOfCoins;
	setText(std::to_string(m_numOfCoins));
}

string CoinView::toString() const
{
	return "CoinView: { " + ImageButton::toString() + " }";
}

void CoinView::checkLegalCoinNum(int numOfCoins) const
{
	if(numOfCoins < 0)
		throw std::out_of_range("Num of Coins - " + std::to_string(numOfCoins) + " - is illegal");
}

void CoinView::init()
{
	getImage().setTexture("coin");
	setTextHAligment(GUI::TextView::TextHAlignment::CENTER);
	setTextSize(30);
	getBorder().setSize(1);
	getBorder().setColor(sf::Color::Black);
}
