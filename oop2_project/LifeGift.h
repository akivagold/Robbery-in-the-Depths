#pragma once
//---- include section ------
#include <string>
#include<memory>
#include "Gift.h"

//---- using section --------
using std::string;

/*
 * LifeGift class
 */
class LifeGift :
	public Gift
{
public:
	// random life gift
	static std::shared_ptr<LifeGift> randLifeGift() { return std::make_shared<LifeGift>(rand() % 6 + 1); }
	// constructor
	explicit LifeGift(int numOfLife = 0);
	// set number of life
	void setNumOfLife(int numOfLife);
	// get num of life
	int getNumOfLife() const { return m_numOfLife; }
	// get info
	virtual string getInfo() const override { return std::to_string(m_numOfLife) + " lifes"; }
	// take surprise
	virtual void takeSurprise(Player* owner);
	// convert to string
	inline virtual string toString() const override; 
private:
	// number of life
	int m_numOfLife;
	// check if is legal life
	bool isLegalLife(int numOfLife) const { return (numOfLife >= 0); }
};

inline string LifeGift::toString() const
{
	return "LifeGift: { numOfLife=" + std::to_string(m_numOfLife) + ", " + Gift::toString() + " }";
}
