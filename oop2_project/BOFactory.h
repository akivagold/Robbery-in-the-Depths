#pragma once
//---- include section ------
#include <string>
#include <map>
#include <functional>
#include <memory>
#include "GameScreen.h"
#include "BoardObject.h"

//---- using section --------
using std::string;

/*
 * Board object factory class
 */
class BOFactory
{
public:
	// create function
	using CreateFunc = std::function<std::shared_ptr<BoardObject>(GameScreen& gameScreen)>;
	// creation map
	using CreationMap = std::map<char, CreateFunc>;
	// get interface
	static BOFactory& getInterface();
	// create new board object
	std::shared_ptr<BoardObject> create(char keyChar, GameScreen& gameScreen);
	// register to creation map
	bool registerIn(char keyChar, CreateFunc createFunc);
	// convert to string
	virtual string toString() const;
private:
	// creation map
	CreationMap m_creationMap;
	// constructor
	BOFactory() = default;
	// disable copy
	BOFactory& operator=(const BOFactory&) = delete;
	BOFactory(const BOFactory&) = delete;
};
