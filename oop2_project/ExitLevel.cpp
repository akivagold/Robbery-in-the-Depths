#include "ExitLevel.h"
#include "BOFactory.h"

// register
bool ExitLevel::isRegistered = BOFactory::getInterface().registerIn(ExitLevel::CHAR, [](GameScreen& gameScreen) { return std::make_shared<ExitLevel>(gameScreen); });


ExitLevel::ExitLevel(GameScreen& gameScreen)
	: StaticObject(gameScreen)
{
	init();
}

void ExitLevel::init()
{
	setAnimation("exit");
	setDrawPriority(DRAW_PRIORITY);
}
