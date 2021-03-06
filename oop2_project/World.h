#pragma once
//---- include section ------
#include <string>
#include "View.h"
#include "BODS.h"
#include "LevelInfo.h"
#include "GameCamera.h"
class GameScreen;

//---- using section --------
using std::string;

/*
 * World class
 */
class World : public GUI::View
{
public:
	// constructor
	explicit World(sf::RenderWindow& window);
	// get BoardObjectDataStructure
	BODS& getBODS() { return m_bods; }
	const BODS& getBODS() const { return m_bods; }
	// load level
	void loadLevel(GameScreen& gameScreen, const LevelInfo& levelInfo);
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override;
protected:
	// handle click event
	virtual bool handleClickEvent(float mouseX, float mouseY) override;
	// handle enter event
	virtual bool handleEnterEvent(float mouseX, float mouseY) override;
	// handle leave event
	virtual bool handleLeaveEvent(float mouseX, float mouseY) override;
	// handle key down event
	virtual void handleKeyDownEvent(sf::Keyboard::Key keyCode) override;
	// handle key released event
	virtual void handleKeyReleasedEvent(sf::Keyboard::Key keyCode) override;
private:
	// BoardObjectDataStructure
	BODS m_bods;
	// init
	void init();
	// game camera
	std::unique_ptr <GameCamera> m_gameCamera;
};

