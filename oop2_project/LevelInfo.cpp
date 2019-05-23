#include "LevelInfo.h"
#include "ParseLevelException.h"

LevelInfo::LevelInfo()
	: m_index(0)
{ }

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

json LevelInfo::convertToJSON(const LevelInfo& levelInfo)
{
	json levelInfoJson;
	levelInfoJson["index"] = levelInfo.getIndex();
	levelInfoJson["name"] = levelInfo.getName();
	levelInfoJson["mapChars"] = convertLevelCharsToStr(levelInfo.getLevelChars());
	json mapSizeJson;
	mapSizeJson["rows"] = levelInfo.getLevelChars().getNumOfRows();
	mapSizeJson["cols"] = levelInfo.getLevelChars().getNumOfCols();
	levelInfoJson["mapSize"] = mapSizeJson;
	return levelInfoJson;
}

LevelInfo LevelInfo::parse(const json& levelInfoJson)
{
	LevelInfo levelInfo;
	try {		
		levelInfo.setIndex(levelInfoJson["index"].get<int>());
		levelInfo.setName(levelInfoJson["name"].get<string>());
		const json& mapSizeJson = levelInfoJson["mapSize"];
		levelInfo.getLevelChars().resize(mapSizeJson["rows"].get<int>(), mapSizeJson["cols"].get<int>());
		putStrInLevelChars(levelInfoJson["mapChars"].get<string>(), levelInfo.getLevelChars());
	}
	catch (const nlohmann::detail::parse_error& ex) { // error when parse JSON
		throw ParseLevelException("Cannot parse level from JSON, the error: " + string(ex.what()));
	}	
	return levelInfo;
}

string LevelInfo::convertLevelCharsToStr(const Matrix<char>& levelChars)
{
	string mapChars = "";
	for (int rowNum = 0; rowNum < levelChars.getNumOfRows(); ++rowNum) {
		for (int colNum = 0; colNum < levelChars.getNumOfCols(); ++colNum) {
			Cell cell(rowNum, colNum);
			mapChars += levelChars[cell];
		}
	}
	return mapChars;
}

void LevelInfo::putStrInLevelChars(const string& charsStr, Matrix<char>& levelChars)
{
	int charIndex = 0;
	for (int rowNum = 0; rowNum < levelChars.getNumOfRows(); ++rowNum) {
		for (int colNum = 0; colNum < levelChars.getNumOfCols(); ++colNum) {
			Cell cell(rowNum, colNum);
			levelChars[cell] = charsStr[charIndex];
			charIndex++;
		}
	}
}
