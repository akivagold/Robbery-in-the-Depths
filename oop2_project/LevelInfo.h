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
	// flow info
	struct FlowInfo
	{
		Cell m_startCell, m_endCell;
		sf::Vector2f flowPower;
	};
	// constructor
	LevelInfo();
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
	// set background music name
	void setBackMusicName(const string& backMusicName) { m_backMusicName = backMusicName; }
	// get background music name
	const string& getBackMusicName() const { return m_backMusicName; }
	// set flows
	void setFlows(const std::vector<FlowInfo>& flows) { m_flows = flows; }
	// get flows
	const std::vector<FlowInfo>& getFlows() const { return m_flows; }
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
	// name 7 background music name
	string m_name, m_backMusicName;
	// level map characters
	Matrix<char> m_levelChars;
	// flows
	std::vector<FlowInfo> m_flows;
	// check if level have legal index
	bool isLegalIndex(int index) const { return (index >= 0); }
	// convert level characters to string
	static string convertLevelCharsToStr(const Matrix<char>& levelChars);
	// put string in level characters
	static void putStrInLevelChars(const string& charsStr, Matrix<char>& levelChars);
	// parse flows
	static std::vector<FlowInfo> parseFlows(const json& flowsJson);
	// parse flow
	static FlowInfo parseFlow(const json& flowJson);
	// build JSON of flows
	static json buildFlowsJSON(const std::vector<FlowInfo>& flows);
	// build JSON of flow
	static json buildFlowJSON(const FlowInfo& flow);
};

