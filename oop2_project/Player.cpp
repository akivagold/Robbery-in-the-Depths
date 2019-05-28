#include "Player.h"
#include "GameScreen.h"

Player::Player(sf::RenderWindow& window, GameScreen& gameScreen, int numOfLife)
	: Character(window, gameScreen)
{}

void Player::changeTool(const std::shared_ptr<Tool>& tool)
{
	//TODO
}

void Player::setLife(int numOfLife) const
{
	Character::setLife(numOfLife);

	// update game menu
	getGameScreen().getGameMenu()->getLifeView()->setLife(numOfLife);
}

void Player::playChoice()
{
	
}

string Player::toString() const
{
	return "Player: { " + Character::toString() + " }";
}
