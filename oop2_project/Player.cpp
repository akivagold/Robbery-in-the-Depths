#include "Player.h"
#include "GameScreen.h"

Player::Player(GameScreen& gameScreen, int numOfLife)
	: Character(gameScreen), m_score(0)
{
	init();
}

void Player::changeTool(const std::shared_ptr<Tool>& tool)
{
	//TODO
}

void Player::setNumOfLife(int numOfLife)
{
	Character::setNumOfLife(numOfLife);

	// update game menu
	getGameScreen().getGameMenu()->getLifeView()->setLife(numOfLife);
}

void Player::onDirectionChanged()
{
	if (getDirection() == Direction::LEFT || getDirection() == Direction::UP_LEFT || getDirection() == Direction::DOWN_LEFT) {
		if (!isFlipped()) {
			flipAnimation(); // turn left
		}
	}
	else if (getDirection() == Direction::RIGHT || getDirection() == Direction::UP_RIGHT || getDirection() == Direction::DOWN_RIGHT) {
		if (isFlipped()) {
			flipAnimation(); // turn right
		}
	}
}

void Player::playChoice(Direction lastDirection, bool isCollided)
{
	// TODO
}

string Player::toString() const
{
	string str = "Player: { currentTool=";
	if (!m_currTool)
		str += "None";
	else
		str += m_currTool->toString();
	str += ", numOfTools=" + std::to_string(m_tools.size());
	str += ", score=" + std::to_string(m_score) + ", ";
	str += Character::toString() + " }";
	return str;
}

void Player::init()
{
	setAnimation("diver_anim");
	setDrawPriority(DRAW_PRIORITY);
	setAnimationFrequency(STAND_ANIM_FREQUENCY);
	
	addKeyDownListener([this](sf::Keyboard::Key& keyCode) {
		setAnimationFrequency(SWIM_ANIM_FREQUENCY);
		float offset = 0.0025f;
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
			} break;
			case sf::Keyboard::Key::Down: {
				getInteralAcceleration().y = offset;
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
