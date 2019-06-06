#pragma once
//---- include section ------
#include <string>
#include "Gift.h"

//---- using section --------
using std::string;

/*
 * CoinGift class
 */
class CoinGift :
	public Gift
{
public:
	// constructor
	explicit CoinGift(int numOfCoins = 0);
	// set number of coins
	void setNumOfCoins(int numOfCoins);
	// get num of coins
	int getNumOfCoins() const { return m_numOfCoins; }
	// take surprise
	virtual void takeSurprise(Player* owner);
	// random coin gift
	static std::shared_ptr<CoinGift> randCoinGift() { return std::make_shared<CoinGift>(rand()%11 + 1); }
	// convert to string
	inline virtual string toString() const override;
private:
	// number of coins
	int m_numOfCoins;
	// check if is legal number of coins
	bool isLegalNumCoins(int numOfCoins) const { return (numOfCoins >= 0); }
};

inline string CoinGift::toString() const
{
	return "CoinGift: { numOfCoins=" + std::to_string(m_numOfCoins) + ", " + Gift::toString() + " }";
}
