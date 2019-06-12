#pragma once
//---- include section ------
#include "BaseScreen.h"
#include "RelativeLayout.h"
#include "EditMenu.h"
#include "EditMapView.h"
#include "GameObjectsList.h"
#include <string>

//---- using section --------
using std::string;

/*
 * EditScreen class
 */
class EditScreen 
	: public GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>
{
public:
	// base class
	using BaseClass = GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>;
	// constructor
	explicit EditScreen(sf::RenderWindow& window);
	// get edit map view
	const std::shared_ptr<EditMapView>& getEditMapView() const { return m_editMapView; }
	// get edit menu
	const std::shared_ptr<EditMenu>& getEditMenu() const { return m_editMenu; }
	// get game objects list
	const std::shared_ptr<GameObjectsList>& getGameObjs() const { return m_gameObjs; }
	// convert to string
	virtual string toString() const override;
private:
	// edit map view
	std::shared_ptr<EditMapView> m_editMapView;
	// edit menu
	std::shared_ptr<EditMenu> m_editMenu;
	// game objects list
	std::vector<GameObjectInfo> m_gois;
	// game objects list
	std::shared_ptr<GameObjectsList> m_gameObjs;
	// init components
	void initComponents();
};

