#pragma once
//---- include section ------
#include <string>
#include "Player.h"
class World;

//---- using section --------
using std::string;

/*
 * GameCamera class
 */
class GameCamera
{
public:
	// constructor
	GameCamera(World* world, const std::shared_ptr<Player>& player);
	// convert to string
	virtual string toString() const { return "Game Camera"; }
	void updateCamera();
private:
	World* m_world;
	const std::shared_ptr<Player>& m_player;
	sf::Clock m_clock;
};

