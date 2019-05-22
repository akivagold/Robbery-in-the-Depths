#include "LevelInfo.h"

void LevelInfo::setIndex(int index)
{
	if (!isLegalIndex(index))
		throw std::out_of_range("The level index (=" + std::to_string(index) + ") must be bigger or equals to 0");
	m_index = index;
}

string LevelInfo::toString() const
{
	return "LevelInfo: { index=" + std::to_string(m_index) + ", name=" + m_name + ", " +
			m_levelChars.toString() + " }";
}
