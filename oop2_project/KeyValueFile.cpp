//---- include section ------
#include "KeyValueFile.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include "LoadResourceException.h"

KeyValueFile::KeyValueFile(const string& fileName)
	: m_fileName(fileName)
{
	loadJsonFromFile();
}

void KeyValueFile::putString(const string& key, const string& value)
{
	putValue(key, value);
}

string KeyValueFile::getString(const string& key, const string& defaultValue) const
{
	return getValue(key, defaultValue);
}

void KeyValueFile::putInt(const string& key, int value)
{
	putValue(key, value);
}

int KeyValueFile::getInt(const string& key, int defaultValue) const
{
	return getValue(key, defaultValue);
}

void KeyValueFile::putBool(const string& key, bool value)
{
	putValue(key, value);
}

bool KeyValueFile::getBool(const string& key, bool defaultValue) const
{
	return getValue(key, defaultValue);
}

void KeyValueFile::putFloat(const string& key, float value)
{
	putValue(key, value);
}

float KeyValueFile::getFloat(const string& key, float defaultValue) const
{
	return getValue(key, defaultValue);
}

void KeyValueFile::clear()
{
	m_fileJson.clear();
	saveFile();
}

void KeyValueFile::removeValue(const string& key)
{
	m_fileJson.erase(key);
	saveFile();
}

string KeyValueFile::toString() const
{
	return "KeyValueFile: fileName=" + m_fileName + ", data=" + m_fileJson.dump();
}

void KeyValueFile::loadJsonFromFile()
{
	// check if file dont exists
	if (!std::filesystem::exists(m_fileName)) {
		// save empty file
		saveFile();
	}

	// open file for read
	std::ifstream file(m_fileName);
	if (!file)
		throw GUI::LoadResourceException("Cannot open file " + m_fileName);
	
	file >> m_fileJson;
	file.close();
}

void KeyValueFile::saveFile()
{
	// open file for write
	std::ofstream file(m_fileName);
	if (!file)
		throw GUI::LoadResourceException("Cannot open file " + m_fileName);
	file << m_fileJson;
	file.close();
}
