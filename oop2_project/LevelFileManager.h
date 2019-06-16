#pragma once
//---- include section ------
#include <string>
#include "LevelInfo.h"

//---- using section --------
using std::string;

/*
 * LevelFileManager class
 */
class LevelFileManager
{
public:
	// constructor
	LevelFileManager() { loadLevels(); }
	// get level (by index)
	const LevelInfo& getLevel(int index) const;
	// get number of levels
	int getNumOfLevels() const { return static_cast<int>(m_levelsInfo.size()); }
	// get level (by name)
	const LevelInfo& getLevel(const string& levelName) const;
	// add new level
	void addLevel(const LevelInfo& levelInfo);
	// edit level (by index)
	void editLevel(const LevelInfo& levelInfo);
	// convert to string
	virtual string toString() const;
private:
	// levels file path
	static const string LEVELS_FILE_PATH;
	// levels info
	std::vector<LevelInfo> m_levelsInfo;
	// load levels
	void loadLevels();
	// read levels file as JSON
	json readLevelsFileJSON() const;
	// build JSON from levels info
	json buildJSON();
	// save file
	void saveFile();
};

