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
	explicit GameCamera(World* world, const std::shared_ptr<Player>& player);
	// update camera
	void updateCamera();
	// convert to string
	virtual string toString() const { return "Game Camera: {}"; }
private:
	// world
	World* m_world;
	// player
	const std::shared_ptr<Player>& m_player;
	// clock
	sf::Clock m_clock;
};

