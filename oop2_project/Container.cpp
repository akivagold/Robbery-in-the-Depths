#include "Container.h"

Container::Container(GameScreen& gameScreen)
	: StaticObject(gameScreen)
{
	// TODO random the surprises
}

string Container::toString() const
{
	string str = "Container: { surprises: {";
	for (auto& surprise : m_surprises) {
		str += surprise->toString() + "\n";
	}
	str += "}, " + StaticObject::toString() + " }";
	return str;
}
