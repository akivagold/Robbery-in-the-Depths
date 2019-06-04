#include "Container.h"
#include "LifeGift.h"
#include "ToolGift.h"

Container::Container(GameScreen& gameScreen)
	: StaticObject(gameScreen)
{
	init();
}

Container::SurprisesList Container::randSurprises()  // TODO must be random!!!!!!!!!!
{
	SurprisesList surprisesList;
	//surprisesList.push_back(std::make_shared<LifeGift>(1));
	surprisesList.push_back(std::make_shared<ToolGift>(Tool::randToolType()));
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
