#include "CoinGift.h"
#include "Player.h"

CoinGift::CoinGift(int numOfCoins)
	: Gift()
{
	setNumOfCoins(numOfCoins);
}

void CoinGift::setNumOfCoins(int numOfCoins)
{
	if(!isLegalNumCoins(numOfCoins))
		std::out_of_range("Number of coins (=" + std::to_string(numOfCoins) + ") must be bigger or equals to zero");
	m_numOfCoins = numOfCoins;
}

void CoinGift::takeSurprise(Player* owner)
{
	owner->appendScore(m_numOfCoins);
	m_numOfCoins = 0;
}
