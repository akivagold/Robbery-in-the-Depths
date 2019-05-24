#include "GOIFileParser.h"
#include "ParseGOIException.h"
#include <fstream>      // std::ifstream

// init
const string GOIFileParser::GOI_FILE_PATH = "game_objects.json";

std::vector<GameObjectInfo> GOIFileParser::parseGOIFile()
{
	std::vector<GameObjectInfo> gois;

	try {
		json goisJSON = readGOIFileJSON();
		const json& goiObjectsJSON = goisJSON.at("gameObjects");
		for (auto it = goiObjectsJSON.cbegin(); it != goiObjectsJSON.cend(); ++it) {
			const json& goiJSON = *it;
			gois.push_back(GameObjectInfo::parse(goiJSON));
		}
	}
	catch (const nlohmann::json::exception& ex) { // error when parse JSON
		throw ParseGOIException("Cannot parse list of GameObjectInfo from JSON, the error: " + string(ex.what()));
	}

	return gois;
}

json GOIFileParser::readGOIFileJSON()
{
	std::ifstream goisFile(GOI_FILE_PATH);
	if (!goisFile.is_open())
		throw ParseGOIException("Cannot find the file '" + GOI_FILE_PATH + "'");
	json goisJSON = json::parse(goisFile);
	goisFile.close();
	return goisJSON;
}
