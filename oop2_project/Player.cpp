#include "Player.h"
#include "GameScreen.h"
#include "Chest.h"
#include "Flow.h"

Player::Player(GameScreen& gameScreen, int numOfLife)
	: Character(gameScreen, numOfLife)
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

void Player::changeTool(const std::shared_ptr<Tool>& tool)
{
	m_currTool = tool;
	getGameScreen().getGameMenu()->getToolView()->setTool(tool);
}

void Player::setNumOfLife(int numOfLife)
{
	Character::setNumOfLife(numOfLife);

	// update game menu
	getGameScreen().getGameMenu()->getLifeView()->setLife(numOfLife);
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
	}
}

void Player::onToolUpdated(Tool* tool)
{
	if(tool == m_currTool.get())
		getGameScreen().getGameMenu()->getToolView()->updateUseLimit();
}

void Player::onCollide(Chest* chest)
{
	if (!chest->isEmpty()) {
		chest->pickup(this);
	}
}

void Player::onCollide(Flow* flow)
{
	setExternaAlcceleration(flow->getFlowPower());
}

void Player::playChoice(Direction lastDirection, bool isCollided)
{
	Character::playChoice(lastDirection, isCollided);
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
	setAnimation("diver_anim");
	setDrawPriority(DRAW_PRIORITY);
	setAnimationFrequency(STAND_ANIM_FREQUENCY);
	setDirection(Direction::RIGHT);
	setMaxSpeed(sf::Vector2f(6.f*getSize().x, 6.f*getSize().y));
	
	addKeyDownListener([this](sf::Keyboard::Key& keyCode) {
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
		}
	});
	addKeyReleasedListener([this](sf::Keyboard::Key& keyCode) {
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
