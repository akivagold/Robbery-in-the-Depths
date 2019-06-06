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
	string str = "LevelInfo: { index=" + std::to_string(m_index) + ", name=" + m_name + ", " + m_levelChars.toString();
	str += ", flows: {\n";
	for (auto& flow : m_flows) {
		str += "flow: { power: { x=" + std::to_string(flow.flowPower.x) + ", y=" + std::to_string(flow.flowPower.y) + " }"
			+ ", startCell=" + flow.m_startCell.toString() + ", endCell=" + flow.m_endCell.toString() + " }\n";
	}
	str += "} }";
	return str;
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
	if (!levelInfo.getFlows().empty()) {
		levelInfoJson["flows"] = buildFlowsJSON(levelInfo.getFlows());
	}
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
		auto flowsIt = levelInfoJson.find("flows");
		if (flowsIt != levelInfoJson.end()) {
			levelInfo.setFlows(parseFlows(*flowsIt));
		}
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

std::vector<LevelInfo::FlowInfo> LevelInfo::parseFlows(const json& flowsJson)
{
	std::vector<FlowInfo> flows;
	for (auto it = flowsJson.cbegin(); it != flowsJson.cend(); ++it)
		flows.push_back(parseFlow(*it));
	return flows;
}

LevelInfo::FlowInfo LevelInfo::parseFlow(const json& flowJson)
{
	FlowInfo flowInfo;
	const json& flowPowerJson = flowJson.at("power");
	flowInfo.flowPower.x = flowPowerJson.at("x").get<float>();
	flowInfo.flowPower.y = flowPowerJson.at("y").get<float>();
	const json& flowFromCellJson = flowJson.at("fromCell");
	flowInfo.m_startCell.setRowNum(flowFromCellJson.at("r").get<int>());
	flowInfo.m_startCell.setColNum(flowFromCellJson.at("c").get<int>());
	const json& flowToCellJson = flowJson.at("toCell");
	flowInfo.m_endCell.setRowNum(flowToCellJson.at("r").get<int>());
	flowInfo.m_endCell.setColNum(flowToCellJson.at("c").get<int>());
	return flowInfo;
}

json LevelInfo::buildFlowsJSON(const std::vector<FlowInfo>& flows)
{
	json flowsJson;
	for (auto& flow : flows)
		flowsJson.push_back(buildFlowJSON(flow));
	return flowsJson;
}

json LevelInfo::buildFlowJSON(const FlowInfo& flow)
{
	json flowJson, flowPowerJson, flowFromCellJson, flowToCellJson;
	flowPowerJson["x"] = flow.flowPower.x;
	flowPowerJson["y"] = flow.flowPower.y;
	flowFromCellJson["r"] = flow.m_startCell.getRowNum();
	flowFromCellJson["c"] = flow.m_startCell.getColNum();
	flowToCellJson["r"] = flow.m_endCell.getRowNum();
	flowToCellJson["c"] = flow.m_endCell.getColNum();
	flowJson["power"] = flowPowerJson;
	flowJson["fromCell"] = flowFromCellJson;
	flowJson["toCell"] = flowToCellJson;
	return flowJson;
}
