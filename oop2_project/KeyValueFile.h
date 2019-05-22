#pragma once
//---- include section ------
#include <string>
#include <nlohmann/json.hpp> // JSON library

//---- using section --------
using std::string;
using Json = nlohmann::json;

/*
 * KeyValueFile class
 */
class KeyValueFile
{
public:
	// constructor
	explicit KeyValueFile(const string& fileName);
	// put string
	void putString(const string& key, const string& value);
	// get string
	string getString(const string& key, const string& defaultValue = "") const;
	// put integer
	void putInt(const string& key, int value);
	// get integer
	int getInt(const string& key, int defaultValue) const;
	// put boolean
	void putBool(const string& key, bool value);
	// get boolean
	bool getBool(const string& key, bool defaultValue) const;
	// put float
	void putFloat(const string& key, float value);
	// get float
	float getFloat(const string& key, float defaultValue) const;
	// clear file
	void clear();
	// remove value according to key
	void removeValue(const string& key);
	// convert to string
	virtual string toString() const;
private:
	// file name
	string m_fileName;
	// file JSON
	Json m_fileJson;
	// put value according to key (value must be primitive type)
	template <class ValueType>
	void putValue(const string& key, const ValueType& value);
	// get value by key. if not found return default value (value must be primitive type)
	template <class ValueType>
	ValueType getValue(const string& key, const ValueType& defaultValue) const;
	// load JSON from file
	void loadJsonFromFile();
	// save file
	void saveFile();
};

template<class ValueType>
void KeyValueFile::putValue(const string& key, const ValueType& value)
{
	m_fileJson[key] = value;
	saveFile();
}

template<class ValueType>
ValueType KeyValueFile::getValue(const string& key, const ValueType& defaultValue) const
{
	auto value = m_fileJson.find(key);
	if (value == m_fileJson.cend())
		return defaultValue;
	return value->get<ValueType>();
}
