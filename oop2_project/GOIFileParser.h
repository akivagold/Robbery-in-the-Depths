#pragma once
//---- include section ------
#include <string>
#include "GameObjectInfo.h"

//---- using section --------
using std::string;

/*
 * GOIFileParser class
 */
class GOIFileParser
{
public:
	// parse list of game object info
	static std::vector<GameObjectInfo> parseGOIFile();
private:
	// levels file path
	static const string GOI_FILE_PATH;
	// read game objects info file as JSON
	static json readGOIFileJSON();
	// cannot create instance of class
	GOIFileParser() = delete;
	// disable copy
	GOIFileParser& operator=(const GOIFileParser&) = delete;
	GOIFileParser(const GOIFileParser&) = delete;
};

