#include "GameObjectInfo.h"
#include "ParseGOIException.h"

GameObjectInfo::GameObjectInfo()
	: GameObjectInfo("", false, 0)
{ }

GameObjectInfo::GameObjectInfo(const string& name, bool isUnique, char specialChar)
{
	setName(name);
	setUnique(isUnique);
	setSpecialChar(specialChar);
}

string GameObjectInfo::toString() const
{
	return "GameObjectInfo: { name=" + m_name + ", isUnique=" + std::to_string(m_isUnique) + ", specialChar=" + string(1, m_specialChar) + " }";
}

GameObjectInfo GameObjectInfo::parse(const json& goiJSON)
{
	GameObjectInfo gameObjectInfo;
	try {
		gameObjectInfo.setName(goiJSON.at("name").get<string>());
		gameObjectInfo.setUnique(goiJSON.at("isUnique").get<bool>());
		gameObjectInfo.setSpecialChar(goiJSON.at("specialChar").get<char>());
	}
	catch (const nlohmann::json::exception& ex) { // error when parse JSON
		throw ParseGOIException("Cannot parse GameObjectInfo from JSON, the error: " + string(ex.what()));
	}
	return gameObjectInfo;
}
