#pragma once
//---- include section ------
#include <string>
#include "TableLayout.h"
#include "MapCellView.h"
#include "Timer.h"
#include "LevelInfo.h"

//---- using section --------
using std::string;

/*
 * EditMapView class
 */
class EditMapView 
	: public GUI::TableLayout<MapCellView>
{
public:	
	// edit mode
	enum EditMode { Add, Remove, None };
	// constructor
	explicit EditMapView(sf::RenderWindow& window, const std::vector<GameObjectInfo>& gois);
	// import level info
	void importLevelInfo(const LevelInfo& levelInfo);
	// set edit mode
	void setEditMode(EditMode editMode) { m_editMode = editMode; }
	// get edit mode
	EditMode getEditMode() const { return m_editMode; }
	// set add char
	void setAddChar(char ch) { m_addChar = ch; }
	// set add char
	char getAddChar(char ch) const { return m_addChar; }
	// export level info
	const LevelInfo& exportLevelInfo();
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override;	
private:
	// base class
	using BaseClass = GUI::TableLayout<MapCellView>;
	// camera animation refresh time in millis
	static const int ANIM_REFRESH_TIME = 17;
	// zoom camera per 1 refresh time
	static const float ZOOM_CAM_ANIM;
	// move camera per 1 refresh time
	static const float MOVE_CAM_ANIM;
	// camera action of editor
	enum CameraAction { RIGHT, LEFT, UP, DOWN, ZOOM_IN, ZOOM_OUT, NONE };
	// convert camera action to string
	static string cameraActToStr(CameraAction cameraAct);
	// current level info
	LevelInfo m_levelInfo;
	// camera movement timer
	Timer m_cameraMoveTimer;
	// current camera action
	CameraAction m_cameraAct;
	// edit mode
	EditMode m_editMode;
	// add char
	char m_addChar;
	// game objects list
	const std::vector<GameObjectInfo>& m_gois;
	// initialize components
	void initComponents();
};

