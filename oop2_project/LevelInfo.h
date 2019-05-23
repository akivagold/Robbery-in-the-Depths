#pragma once
//---- include section ------
#include <string>
#include "Matrix.h"
#include <nlohmann/json.hpp> // JSON library

//---- using section --------
using std::string;
using json = nlohmann::json;
/*
 * LevelInfo class
 */
class LevelInfo
{
public:
	// constructor
	LevelInfo() = default;
	// get level map characters
	Matrix<char>& getLevelChars() { return m_levelChars; }
	const Matrix<char>& getLevelChars() const { return m_levelChars; } // for const access
	// set index
	void setIndex(int index);
	// get index
	int getIndex() const { return m_index; }
	// set name
	void setName(const string& name) { m_name = name; }
	// get name
	const string& getName() const { return m_name; }
	// convert to JSON
	json toJSON() const { return convertToJSON(*this); }
	// convert to string
	virtual string toString() const;
	// convert level info to JSON
	static json convertToJSON(const LevelInfo& levelInfo);
	// parse level info from JSON
	static LevelInfo parse(const json& levelInfoJson);
private:
	// level index
	int m_index;
	// name
	string m_name;
	// level map characters
	Matrix<char> m_levelChars;
	// check if level have legal index
	bool isLegalIndex(int index) const { return (index >= 0); }
	// convert level characters to string
	static string convertLevelCharsToStr(const Matrix<char>& levelChars);
	// put string in level characters
	static void putStrInLevelChars(const string& charsStr, Matrix<char>& levelChars);
};

