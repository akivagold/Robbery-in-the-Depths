#pragma once
//---- include section ------
#include <string>
#include <SFML/Graphics.hpp>
#include <functional>

//---- using section ----------------
using std::string;

/*
 * Utilites namespace
 */
namespace Utilities {
	// convert key code to string
	string keyCodeToString(sf::Keyboard::Key keyCode);	
	// join string
	template <class DS, class CIt>
	string join(const string& separator, const DS& dataStruct, std::function<string(CIt)> convertToStr);
}

template<class DS, class CIt>
string Utilities::join(const string& separator, const DS& dataStruct, std::function<string(CIt)> convertToStr)
{
	string str = "";
	for (auto it = dataStruct.cbegin(); it != dataStruct.cend(); ++it) {
		str += convertToStr(it) + separator;
	}
	if(!str.empty())
		str = str.substr(0, str.length() - separator.length());
	return str;
}
