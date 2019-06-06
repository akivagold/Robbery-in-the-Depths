#include "Container.h"
#include "LifeGift.h"
#include "ToolGift.h"
#include "CoinGift.h"

Container::Container(GameScreen& gameScreen)
	: StaticObject(gameScreen)
{
	init();
}

Container::SurprisesList Container::randSurprises()
{
	SurprisesList surprisesList;
	surprisesList.push_back(CoinGift::randCoinGift()); // always have coins
	if(rand()%2 == 0)
		surprisesList.push_back(LifeGift::randLifeGift());
	if(rand()%2 == 0)
		surprisesList.push_back(ToolGift::randToolGift());
	return surprisesList;
}

void Container::init()
{
	m_surprises = randSurprises();
}

void Container::pickup(Player* owner)
{
	for (auto& suprise : m_surprises)
		suprise->takeSurprise(owner);
	clearSurprises();
}

string Container::toString() const
{
	string str = "Container: { surprises: { ";
	for (auto& surprise : m_surprises) {
		str += surprise->toString() + "\n";
	}
	str += " }, " + StaticObject::toString() + " }";
	return str;
}
