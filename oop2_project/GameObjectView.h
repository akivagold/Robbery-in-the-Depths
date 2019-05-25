#pragma once
//---- include section ------
#include <string>
#include "ImageView.h"
#include "GameObjectInfo.h"

//---- using section --------
using std::string;

/*
 * GameObjectView class
 */
class GameObjectView :
	public GUI::ImageView
{
public:
	// constructor
	explicit GameObjectView(sf::RenderWindow& window, const GameObjectInfo& gameObjectInfo);
	// get game object info
	const GameObjectInfo& getGameObjectInfo() const { return m_gameObjectInfo; }
	// convert to string
	virtual string toString() const override;
private:
	// game object info
	GameObjectInfo m_gameObjectInfo;
	// init components
	void initComponents();
};

