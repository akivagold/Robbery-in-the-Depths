#include "Player.h"
#include "GameScreen.h"
#include "Chest.h"
#include "Flow.h"
#include "SoundManager.h"
#include "Explosion.h"
#include "BOFactory.h"
#include "Bullet.h"
#include "Shark.h"
#include "Crab.h"
#include "Grenade.h"
#include "ExitLevel.h"

// time to wall recover
static const double WALL_RECOVERY_TIME = 1000;

// register
bool Player::isRegistered = BOFactory::getInterface().registerIn(Player::CHAR, [](GameScreen& gameScreen) { return std::make_shared<Player>(gameScreen); });

Player::Player(GameScreen& gameScreen, int numOfLife)
	: Character(gameScreen, numOfLife), m_isRecover(false),m_isWallRecover(false)
{
	init();
}

void Player::addTool(const std::shared_ptr<Tool>& tool)
{
	if (isWithoutTools())
		changeTool(tool);
	m_tools.push_back(tool);
}

void Player::setNumOfScore(int numOfScore)
{
	if (numOfScore < 0)
		throw std::out_of_range("Number of score (=" + std::to_string(numOfScore) + ") must be bigger or equals to zero");
	m_numOfScore = numOfScore;
	getGameScreen().getGameMenu()->getCoinView()->setNumOfCoins(numOfScore);
}

void Player::appendScore(int numOfScore)
{
	setNumOfScore(getNumOfScore() + numOfScore);
}

const std::shared_ptr<Tool>& Player::getTool(Tool::ToolType toolType) const
{
	auto it = std::find_if(m_tools.cbegin(), m_tools.cend(), [toolType](const std::shared_ptr<Tool>& currTool) {
		return (currTool->getToolType() == toolType);
	});
	if (it == m_tools.cend())
		throw std::out_of_range("Cannot find the tool type " + std::to_string(toolType));
	return *it;
}

bool Player::haveTool(Tool::ToolType toolType) const
{
	auto it = std::find_if(m_tools.cbegin(), m_tools.cend(), [toolType](const std::shared_ptr<Tool>& currTool) {
		return (currTool->getToolType() == toolType);
	});
	return (it != m_tools.cend());
}

bool Player::haveTool(Tool* tool) const
{
	return haveTool(tool->getToolType());
}

void Player::switchToNextTool()
{
	if (haveCurrTool()) {
		int currentToolIndex = findToolIndex(m_currTool);
		int nextToolIndex;
		if (currentToolIndex + 1 == m_tools.size())
			nextToolIndex = 0;
		else
			nextToolIndex = currentToolIndex + 1;
		auto& nextTool = m_tools[nextToolIndex];
		changeTool(nextTool);
		playSound("change_tool");
	}
}

void Player::changeTool(const std::shared_ptr<Tool>& tool)
{
	m_currTool = tool;
	getGameScreen().getGameMenu()->getToolView()->setTool(tool);
}

void Player::setNumOfLife(int numOfLife)
{
	Character::setNumOfLife(numOfLife);

	// update game menu
	getGameScreen().getGameMenu()->getLifeView()->setNumOfLife(numOfLife);
}

void Player::onDirectionChanged()
{
	if (isLeftDirections(getDirection())) {
		if (!isFlipped()) {
			flipAnimation(); // turn left
		}
	}
	else if (isRightDirections(getDirection())) {
		if (isFlipped()) {
			flipAnimation(); // turn right
		}
	}
}

void Player::useCurrTool()
{
	if (haveCurrTool()) {
		if (m_currTool->canUsingTool()) {
			m_currTool->useTool();
		}
		else {
			playSound("no_ammo");
		}
	}
}

void Player::onToolUpdated(Tool* tool)
{
	if (tool == m_currTool.get())
		getGameScreen().getGameMenu()->getToolView()->updateUseLimit();
}

void Player::decreaseLife(int numOfLife)
{
	Character::decreaseLife(numOfLife);
	if (numOfLife > 0) {
		GUI::SoundManager::getInterface().playSound("player_hurt");
		recover();
	}
}

void Player::onDie()
{
	Character::onDie();
	if (m_dieHandler)
		m_dieHandler();
}

void Player::onVanish()
{
	Character::onVanish();
	if (m_vanishHandler)
		m_vanishHandler();
}

void Player::onCollide(Shark* shark)
{
	if (!isDie() && !isRecover() && !shark->isDie()) {
		decreaseLife(shark->getDamage());
		GUI::SoundManager::getInterface().playSound("bite_sound");
	}
}

void Player::onCollide(Crab* crab)
{
	if (!isDie() && !isRecover() && !crab->isDie()) {
		decreaseLife(crab->getDamage());
	}
}

void Player::onCollide(Chest* chest)
{
	if (!chest->isEmpty()) {
		string message = "You received " + chest->getContentInfo();
		getGameScreen().getGameAnimText()->showText(GameAnimText::TextInfo(message, sf::Color(108, 0, 118)));
		chest->pickup(this);		
	}
}

void Player::onCollide(Flow* flow)
{
	setExternaAlcceleration(getExternaAlcceleration() + flow->getFlowPower());
}

void Player::onCollide(Bullet* bullet)
{
	if (bullet->getMyOwner() != this) {
		if (!isDie() && !bullet->isInShotTime()) {
			if (!isRecover())
				decreaseLife(bullet->getDamage());
			bullet->explode();
		}
	}
}

void Player::onCollide(Grenade* grenade)
{
	if (grenade->getMyOwner() != this) {
		if (!isDie() && !grenade->isInShotTime()) {
			if (!isRecover())
				decreaseLife(grenade->getDamage());
			grenade->explode();
		}
	}
}

void Player::onCollide(Explosion* explosion)
{
	sf::Vector2f moveDir = getCenter() - explosion->getCenter();
	sf::Vector2f exAcc = explosion->getPower()*moveDir;
	exAcc.x /= float(getSize().x);
	exAcc.y /= float(getSize().y);
	setExternaAlcceleration(exAcc);
}

void Player::onCollide(ExitLevel* exitLevel)
{
	if (m_comeToELHandler)
		m_comeToELHandler();
}

void Player::playChoice(Direction lastDirection, bool isCollided)
{
	Character::playChoice(lastDirection, isCollided);
	m_recoveSW.checkStopWatch();
	checkWallRecoverClock();
}

string Player::toString() const
{
	string str = "Player: { currentTool=";
	if (!haveCurrTool())
		str += "None";
	else
		str += m_currTool->toString();
	str += ", numOfTools=" + std::to_string(m_tools.size());
	str += ", score=" + std::to_string(m_numOfScore) + ", ";
	str += Character::toString() + " }";
	return str;
}

void Player::init()
{
	setNumOfScore(0);
	setNumOfLife(getNumOfLife()); // update number of life in menu
	setAnimation("diver_anim");
	setDrawPriority(DRAW_PRIORITY);
	setAnimationFrequency(STAND_ANIM_FREQUENCY);
	setDirection(Direction::RIGHT);
	setSize(static_cast<int>(0.7f*getDefaultSize().x), static_cast<int>(0.5f*getDefaultSize().y));
	setMaxSpeed(sf::Vector2f(6.f*getSize().x, 6.f*getSize().y));

	addKeyDownListener([this](sf::Keyboard::Key& keyCode) {
		if (isDie())
			return;

		setAnimationFrequency(SWIM_ANIM_FREQUENCY);
		float offset = 0.00005f*float(getSize().x);
		switch (keyCode)
		{
		case sf::Keyboard::Key::Left: {
			getInteralAcceleration().x = -offset;
			setDirection(Direction::LEFT);
		} break;
		case sf::Keyboard::Key::Right: {
			getInteralAcceleration().x = offset;
			setDirection(Direction::RIGHT);
		} break;
		case sf::Keyboard::Key::Up: {
			getInteralAcceleration().y = -offset;
			//setDirection(Direction::UP);
		} break;
		case sf::Keyboard::Key::Down: {
			getInteralAcceleration().y = offset;
			//setDirection(Direction::DOWN);
		} break;
		case sf::Keyboard::Key::Space: {
			useCurrTool();
		} break;
		case sf::Keyboard::Key::LShift: {
			switchToNextTool();
		} break;
		}
	});
	addKeyReleasedListener([this](sf::Keyboard::Key& keyCode) {
		if (isDie())
			return;

		setAnimationFrequency(STAND_ANIM_FREQUENCY);
		float offset = 0;
		switch (keyCode)
		{
		case sf::Keyboard::Key::Left: {
			getInteralAcceleration().x = -offset;
		} break;
		case sf::Keyboard::Key::Right: {
			getInteralAcceleration().x = offset;
		} break;
		case sf::Keyboard::Key::Up: {
			getInteralAcceleration().y = -offset;
		} break;
		case sf::Keyboard::Key::Down: {
			getInteralAcceleration().y = offset;
		} break;
		}
	});
}

int Player::findToolIndex(const std::shared_ptr<Tool>& tool)
{
	for (int i = 0; i < m_tools.size(); ++i) {
		if (m_tools[i] == tool)
			return i;
	}
	throw std::out_of_range("Cannot find the tool " + tool->toString());
}

void Player::recover()
{
	m_isRecover = true;
	m_recoveSW.start(RECOVERY_TIME, [this]() {
		m_isRecover = false;
	});
}

void Player::onCollide(Wall* wall)
{
	if (wallRecoveryClock.getElapsedTime().asMilliseconds() < WALL_RECOVERY_TIME/8) {
		m_isWallRecover = true;
	}
	checkWallRecoverClock();
}

const sf::Vector2f Player::getExternaAlcceleration() const {
	if (isWallRecover()) {
		return sf::Vector2f(0, 0);
	}
	return MovingObject::getExternaAlcceleration();
}

void Player::checkWallRecoverClock() {
	if (wallRecoveryClock.getElapsedTime().asMilliseconds() > WALL_RECOVERY_TIME / 8) {
		m_isWallRecover = false;
	}
	if (wallRecoveryClock.getElapsedTime().asMilliseconds() > WALL_RECOVERY_TIME) {
		wallRecoveryClock.restart();
	}
}