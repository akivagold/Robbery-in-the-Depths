#include "BOFactory.h"
#include "Utilities.h"

BOFactory& BOFactory::getInterface()
{
	static BOFactory boFactory;
	return boFactory;
}

std::shared_ptr<BoardObject> BOFactory::create(char keyChar, GameScreen& gameScreen)
{
	auto it = m_creationMap.find(keyChar);
	if (it == m_creationMap.end())
		throw std::invalid_argument("Cannot find board object with char=" + string(1, keyChar) + " at BOFactory");
	return it->second(gameScreen);
}

bool BOFactory::registerIn(char keyChar, CreateFunc createFunc)
{
	m_creationMap[keyChar] = createFunc;
	return true;
}

string BOFactory::toString() const
{
	string str = "BOFactory: { creationMap-keys: {";	
	str += Utilities::join<CreationMap, CreationMap::const_iterator>(",", m_creationMap, [](CreationMap::const_iterator el) -> string { return string(1, el->first); });
	str += " } }";
	return str;
}
