#include "World.h"
#include "Player.h"
#include "Wall.h"
#include "Chest.h"
#include "Shark.h"
#include "Cop.h"
#include "Crab.h"
#include "ParseLevelException.h"

World::World(sf::RenderWindow& window)
	: GUI::View(window)
{
	init();
}

void World::loadLevel(GameScreen& gameScreen, const LevelInfo& levelInfo)
{
	const sf::Vector2i& defaultSize = BoardObject::getDefaultSize();
	sf::Vector2i levelSize = levelInfo.getLevelChars().getSize();
	setSize(levelSize.x*defaultSize.y, levelSize.y*defaultSize.x);

	for (auto it = levelInfo.getLevelChars().cbegin(); it != levelInfo.getLevelChars().cend(); ++it) {
		const Cell& cell = it.getCell();
		char ch = *it;
		if (ch != ' ') {
			sf::Vector2f position(static_cast<float>(defaultSize.x*cell.getColNum()), static_cast<float>(defaultSize.y*cell.getRowNum()));
			std::shared_ptr<BoardObject> boardObj = createBO(gameScreen, ch);
			boardObj->setPosition(position);
			m_bods.requestAddBO(boardObj);
		}	
	}

	// TODO load flows, etc.

	m_bods.prepareLevel();
}

std::shared_ptr<BoardObject> World::createBO(GameScreen& gameScreen, char ch)
{
	std::shared_ptr<BoardObject> boardObj;
	switch (ch)
	{
		case Player::CHAR: {
			boardObj = std::make_shared<Player>(gameScreen);
		} break;
		case Crab::CHAR: {
			boardObj = std::make_shared<Crab>(gameScreen);
		} break;
		case Wall::CHAR: {
			boardObj = std::make_shared<Wall>(gameScreen);
		} break;
		case Chest::CHAR: {
			boardObj = std::make_shared<Chest>(gameScreen);
		} break;
		case Cop::CHAR: {
			// TODO boardObj = std::make_shared<Cop>(gameScreen);
		} break;
		case Shark::CHAR: {
			boardObj = std::make_shared<Shark>(gameScreen);
		} break;
		default:
			throw ParseLevelException("Cannot parse board object with char=" + string(1, ch));
	}
	return boardObj;
}

void World::draw()
{
	View::draw();
	if (isShow()) {
		for (auto& boardObject : m_bods.getBOs()) {
			boardObject->draw();
		}
	}	
}

void World::init()
{
	makeRootView(true);
	setPosition(0, 0);
	getBackground().setColor(sf::Color::White);
	getBorder().setColor(sf::Color::Blue);
	getBorder().setSize(1);
}


string World::toString() const
{
	return "World: { " + m_bods.toString() + " }";
}

bool World::handleClickEvent(float mouseX, float mouseY)
{
	bool clicked = View::handleClickEvent(mouseX, mouseY);
	if (isEnable()) {		
		for (auto& boardObject : m_bods.getBOs()) {
			boardObject->handleClickEvent(mouseX, mouseY);
		}
	}
	return clicked;
}

bool World::handleEnterEvent(float mouseX, float mouseY)
{
	bool entered = View::handleEnterEvent(mouseX, mouseY);
	if (isEnable()) {
		for (auto& boardObject : m_bods.getBOs()) {
			boardObject->handleEnterEvent(mouseX, mouseY);
		}
	}
	return entered;
}

bool World::handleLeaveEvent(float mouseX, float mouseY)
{
	bool entered = View::handleLeaveEvent(mouseX, mouseY);
	if (isEnable()) {
		for (auto& boardObject : m_bods.getBOs()) {
			boardObject->handleLeaveEvent(mouseX, mouseY);
		}
	}
	return entered;
}

void World::handleKeyDownEvent(sf::Keyboard::Key keyCode)
{
	View::handleKeyDownEvent(keyCode);

	if (isEnable()) {
		for (auto& boardObject : m_bods.getBOs()) {
			boardObject->handleKeyDownEvent(keyCode);
		}
	}
}

void World::handleKeyReleasedEvent(sf::Keyboard::Key keyCode)
{
	View::handleKeyReleasedEvent(keyCode);

	if (isEnable()) {
		for (auto& boardObject : m_bods.getBOs()) {
			boardObject->handleKeyReleasedEvent(keyCode);
		}
	}
}


