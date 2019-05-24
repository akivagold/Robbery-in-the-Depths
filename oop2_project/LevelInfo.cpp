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
		levelInfo.setIndex(levelInfoJson.at("index").get<int>());
		levelInfo.setName(levelInfoJson.at("name").get<string>());
		const json& mapSizeJson = levelInfoJson.at("mapSize");
		levelInfo.getLevelChars().resize(mapSizeJson.at("rows").get<int>(), mapSizeJson.at("cols").get<int>());
		putStrInLevelChars(levelInfoJson.at("mapChars").get<string>(), levelInfo.getLevelChars());
	}
	catch (const nlohmann::json::exception& ex) { // error when parse JSON
		throw ParseLevelException("Cannot parse level from JSON, the error: " + string(ex.what()));
	}	
	return levelInfo;
}

string LevelInfo::convertLevelCharsToStr(const Matrix<char>& levelChars)
{
	string mapChars = "";
	for (char c : levelChars) {
		mapChars += c;
	}
	return mapChars;
}

void LevelInfo::putStrInLevelChars(const string& charsStr, Matrix<char>& levelChars)
{
	int charIndex = 0;
	for (Matrix<char>::iterator it = levelChars.begin(); it != levelChars.end(); ++it) {
		*it = charsStr[charIndex];
		++charIndex;
	}
}
