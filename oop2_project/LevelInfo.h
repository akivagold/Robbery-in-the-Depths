#pragma once
//---- include section ------
#include <string>
#include "Matrix.h"
#include <nlohmann/json.hpp> // JSON library

//---- using section --------
using std::string;

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
	// set index
	void setIndex(int index);
	// get index
	int getIndex() const { return m_index; }
	// set name
	void setName(const string& name) { m_name = name; }
	// get name
	const string& getName() const { return m_name; }
	// convert to string
	virtual string toString() const;
	// convert level info to JSON
	//static JSON convertToJSON(const LevelInfo&)
	//static LevelInfo parse(c JSON&)

private:
	// level index
	int m_index;
	// name
	string m_name;
	// level map characters
	Matrix<char> m_levelChars;
	// check if level have legal index
	bool isLegalIndex(int index) const { return (index >= 0); }
};

