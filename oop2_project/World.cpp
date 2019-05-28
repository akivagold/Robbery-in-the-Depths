#include "World.h"

// init 
const sf::Vector2i World::BO_REG_SIZE(50, 50);

World::World(sf::RenderWindow& window)
	: GUI::View(window)
{
	init();
}

void World::loadLevel(const LevelInfo& levelInfo)
{
	sf::Vector2i levelSize = levelInfo.getLevelChars().getSize();
	setSize(levelSize.x*BO_REG_SIZE.y, levelSize.y*BO_REG_SIZE.x);

	// TODO 

	//m_bods.prepareLevel();
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

void World::init()
{
	makeRootView(true);
	setPosition(0, 0);
	getBackground().setColor(sf::Color::White);
	getBorder().setColor(sf::Color::Blue);
	getBorder().setSize(1);
}
