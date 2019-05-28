#include "Player.h"
#include "GameScreen.h"

Player::Player(GameScreen& gameScreen, int numOfLife)
	: Character(gameScreen)
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

void Player::playChoice()
{
	// TODO
}

string Player::toString() const
{
	return "Player: { " + Character::toString() + " }";
}

void Player::init()
{
	setAnimation("coin"); // TODO change
	//setAnimationFrequency(?)
	addKeyDownListener([this](sf::Keyboard::Key& keyCode) {
		float offset = 5;
		switch (keyCode)
		{
			case sf::Keyboard::Key::Left: {
				getSpeed().x = -offset;
			} break;
			case sf::Keyboard::Key::Right: {
				getSpeed().x = offset;
			} break;
			case sf::Keyboard::Key::Up: {
				getSpeed().y = -offset;
			} break;
			case sf::Keyboard::Key::Down: {
				getSpeed().y = offset;
			} break;
		}
	});
	addKeyReleasedListener([this](sf::Keyboard::Key& keyCode) {
		float offset = 0;
		switch (keyCode)
		{
		case sf::Keyboard::Key::Left: {
			getSpeed().x = -offset;
		} break;
		case sf::Keyboard::Key::Right: {
			getSpeed().x = offset;
		} break;
		case sf::Keyboard::Key::Up: {
			getSpeed().y = -offset;
		} break;
		case sf::Keyboard::Key::Down: {
			getSpeed().y = offset;
		} break;
		}
	});
}
