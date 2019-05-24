#pragma once
//---- include section ------
#include <string>
#include <nlohmann/json.hpp> // JSON library

//---- using section --------
using std::string;
using json = nlohmann::json;

/*
 * GameObjectInfo class
 */
class GameObjectInfo
{
public:
	// constructors
	GameObjectInfo();
	explicit GameObjectInfo(const string& name, bool isUnique, char specialChar);
	// set name
	void setName(const string& name) { m_name = name; }
	// get name
	const string& getName() const { return m_name; }
	// set unique flag
	void setUnique(bool isUnique) { m_isUnique = isUnique; }
	// check if is unique
	bool isUnique() const { return m_isUnique; }
	// set special character
	void setSpecialChar(char specialChar) { m_specialChar = specialChar; }
	// get special character
	char getSpecialChar() const { return m_specialChar; }
	// convert to string
	virtual string toString() const;
	// parse GameObjectInfo from JSON
	static GameObjectInfo parse(const json& goiJSON);
private:
	// name
	string m_name;
	// unique flag
	bool m_isUnique;
	// special character
	char m_specialChar;
};

