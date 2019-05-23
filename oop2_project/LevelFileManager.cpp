#include "LevelFileManager.h"
#include <fstream>      // std::ifstream
#include "ParseLevelException.h"

// init
const string LevelFileManager::LEVELS_FILE_PATH = "levels.json";

const LevelInfo& LevelFileManager::getLevel(int index) const
{	
	auto it = std::find_if(m_levelsInfo.cbegin(), m_levelsInfo.cend(), [index](const LevelInfo& li) { return li.getIndex() == index; });
	if(it == m_levelsInfo.cend())
		throw ParseLevelException("Cannot find the level with index=" + std::to_string(index));
	return *it;
}

const LevelInfo& LevelFileManager::getLevel(const string& levelName) const
{
	auto it = std::find_if(m_levelsInfo.cbegin(), m_levelsInfo.cend(), [&levelName](const LevelInfo& li) { return li.getName() == levelName; });
	if (it == m_levelsInfo.cend())
		throw ParseLevelException("Cannot find the level with name=" + levelName);
	return *it;
}

void LevelFileManager::addLevel(const LevelInfo& levelInfo)
{
	m_levelsInfo.push_back(levelInfo);
	saveFile();
}

void LevelFileManager::editLevel(const LevelInfo& levelInfo)
{
	if(levelInfo.getIndex() < 0 || levelInfo.getIndex() >= getNumOfLevels())
		throw ParseLevelException("Cannot find the level with index=" + std::to_string(levelInfo.getIndex()));
	m_levelsInfo[levelInfo.getIndex()] = levelInfo;
	saveFile();
}

string LevelFileManager::toString() const
{
	string str = "LevelFileManager: { levelsFileName=" + LEVELS_FILE_PATH + " } levels: { ";
	for (const LevelInfo& levelInfo : m_levelsInfo) {
		str += levelInfo.toString() + ", ";
	}
	str += " } }";
	return str;
}

void LevelFileManager::loadLevels()
{
	json levelsFileJSON = readLevelsFileJSON();
	const json& levelsArray = levelsFileJSON["levels"];
	for (json::const_iterator it = levelsArray.begin(); it != levelsArray.end(); ++it) {
		m_levelsInfo.push_back(LevelInfo::parse(*it));
	}
}

json LevelFileManager::readLevelsFileJSON() const
{
	std::ifstream levelsFile(LEVELS_FILE_PATH);
	if (!levelsFile.is_open())
		throw ParseLevelException("Cannot find the file '" + LEVELS_FILE_PATH + "'");
	json levelsFileJSON = json::parse(levelsFile);
	levelsFile.close();
	return levelsFileJSON;
}

json LevelFileManager::buildJSON()
{
	json levelsFileJSON;
	for (const LevelInfo& levelInfo : m_levelsInfo) {
		levelsFileJSON["levels"].push_back(levelInfo.toJSON());
	}
	return levelsFileJSON;
}

void LevelFileManager::saveFile()
{
	json levelsInfo;
	std::ofstream levelsFile(LEVELS_FILE_PATH);
	levelsFile << buildJSON();
	levelsFile.close();
}
