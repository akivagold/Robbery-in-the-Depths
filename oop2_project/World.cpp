#include "World.h"
#include "Player.h"
#include "Wall.h"
#include "Chest.h"
#include "Shark.h"
#include "Crab.h"
#include "Rubber.h"
#include "Flow.h"
#include "ParseLevelException.h"
#include "BOFactory.h"
#include <iostream>

World::World(sf::RenderWindow& window)
	: GUI::View(window)
{
	init();
}

void World::loadLevel(GameScreen& gameScreen, const LevelInfo& levelInfo)
{
	const sf::Vector2i& defaultSize = BoardObject::getDefaultSize();
	sf::Vector2i levelSize = levelInfo.getLevelChars().getSize();
	setSize(levelSize.y*defaultSize.y, levelSize.x*defaultSize.x);

	for (auto it = levelInfo.getLevelChars().cbegin(); it != levelInfo.getLevelChars().cend(); ++it) {
		const Cell& cell = it.getCell();
		char ch = *it;
		if (ch != ' ') {
			sf::Vector2f position(static_cast<float>(defaultSize.x*cell.getColNum()), static_cast<float>(defaultSize.y*cell.getRowNum()));
			std::shared_ptr<BoardObject> boardObj = BOFactory::getInterface().create(ch, gameScreen);
			// fix position
			if (getSize().y != defaultSize.y) {
				position.y += (defaultSize.y - boardObj->getSize().y)*0.6f;
			}
			if (getSize().x != defaultSize.x) {
				position.x += (defaultSize.x - boardObj->getSize().x)/2.f;
			}
			boardObj->setPosition(position);
			m_bods.requestAddBO(boardObj);
		}	
	}

	// load flows
	for (auto& flowInfo : levelInfo.getFlows()) {
		sf::Vector2f position(static_cast<float>(defaultSize.x*flowInfo.m_startCell.getColNum()), static_cast<float>(defaultSize.y*flowInfo.m_startCell.getRowNum()));
		Cell dCell = flowInfo.m_endCell - flowInfo.m_startCell;
		sf::Vector2i size(defaultSize.x*dCell.getRowNum(), defaultSize.y*dCell.getColNum());
		std::shared_ptr<Flow> flow = std::make_shared<Flow>(gameScreen);
		flow->setPosition(position);
		flow->setSize(size);
		flow->setFlow(flowInfo.flowPower);
		m_bods.requestAddBO(flow);
	}

	m_bods.prepareLevel();

	m_gameCamera = std::make_unique<GameCamera>(this, getBODS().getPlayer());
}

void World::draw()
{
	if (m_gameCamera) {
		m_gameCamera->updateCamera();
	}
	
	View::draw();
	if (isShow()) {
		for (auto& boSetPair : m_bods.getBOs()) {
			for(auto& boardObject : boSetPair.second)
				boardObject->draw();
		}
	}	
	
}

void World::init()
{
	makeRootView(true);
	setPosition(0, 0);
	getBackground().setTexture("water_texture3");
	const_cast<sf::Texture*>(getBackground().getSpriteTexture().getTexture())->setRepeated(true);
	const_cast<sf::Texture*>(getBackground().getSpriteTexture().getTexture())->setSmooth(true);
	getBorder().setSize(1);
	getCamera().zoom(0.6f);
	getCamera().setViewport(sf::FloatRect(0.f, 0.2f, 1.f, 0.8f));
	getCamera().setCenter(sf::Vector2f(getCenter()));
}


string World::toString() const
{
	return "World: { " + m_bods.toString() + " }";
}

bool World::handleClickEvent(float mouseX, float mouseY)
{
	bool clicked = View::handleClickEvent(mouseX, mouseY);
	if (isEnable()) {		
		for (auto& boSetPair : m_bods.getBOs())
			for (auto& boardObject : boSetPair.second)
				boardObject->handleClickEvent(mouseX, mouseY);
	}
	return clicked;
}

bool World::handleEnterEvent(float mouseX, float mouseY)
{
	bool entered = View::handleEnterEvent(mouseX, mouseY);
	if (isEnable()) {
		for (auto& boSetPair : m_bods.getBOs())
			for (auto& boardObject : boSetPair.second)
				boardObject->handleEnterEvent(mouseX, mouseY);
	}
	return entered;
}

bool World::handleLeaveEvent(float mouseX, float mouseY)
{
	bool entered = View::handleLeaveEvent(mouseX, mouseY);
	if (isEnable()) {
		for (auto& boSetPair : m_bods.getBOs())
			for (auto& boardObject : boSetPair.second)
				boardObject->handleLeaveEvent(mouseX, mouseY);
	}
	return entered;
}

void World::handleKeyDownEvent(sf::Keyboard::Key keyCode)
{
	View::handleKeyDownEvent(keyCode);

	if (isEnable()) {
		for (auto& boSetPair : m_bods.getBOs())
			for (auto& boardObject : boSetPair.second)
				boardObject->handleKeyDownEvent(keyCode);
	}
}

void World::handleKeyReleasedEvent(sf::Keyboard::Key keyCode)
{
	View::handleKeyReleasedEvent(keyCode);

	if (isEnable()) {
		for (auto& boSetPair : m_bods.getBOs())
			for (auto& boardObject : boSetPair.second)
				boardObject->handleKeyReleasedEvent(keyCode);
	}
}


