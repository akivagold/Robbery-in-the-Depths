#include "LifeGift.h"
#include "Player.h"

LifeGift::LifeGift(int numOfLife)
	: Gift()
{
	setNumOfLife(numOfLife);
}

void LifeGift::setNumOfLife(int numOfLife)
{
	if (!isLegalLife(numOfLife))
		std::out_of_range("Number of life (=" + std::to_string(numOfLife) + ") must be bigger or equals to zero");
	m_numOfLife = numOfLife;
}

void LifeGift::takeSurprise(Player* owner)
{
	owner->setNumOfLife(owner->getNumOfLife() + m_numOfLife);
	m_numOfLife = 0; // clear surprise
}

