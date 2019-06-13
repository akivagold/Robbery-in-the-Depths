#include "Flow.h"
#include "MovingObject.h"
#include "BOFactory.h"

// register
bool Flow::isRegisteredLeft = BOFactory::getInterface().registerIn(Flow::LEFT_CHAR, [](GameScreen& gameScreen) { return std::make_shared<Flow>(gameScreen, sf::Vector2f{ -Flow::XY_DEFAULT_POWER, 0.f }); });
bool Flow::isRegisteredRight = BOFactory::getInterface().registerIn(Flow::RIGHT_CHAR, [](GameScreen& gameScreen) { return std::make_shared<Flow>(gameScreen, sf::Vector2f{ Flow::XY_DEFAULT_POWER, 0.f }); });
bool Flow::isRegisteredUp = BOFactory::getInterface().registerIn(Flow::UP_CHAR, [](GameScreen& gameScreen) { return std::make_shared<Flow>(gameScreen, sf::Vector2f{ 0.f, -Flow::XY_DEFAULT_POWER }); });
bool Flow::isRegisteredDown = BOFactory::getInterface().registerIn(Flow::DOWN_CHAR, [](GameScreen& gameScreen) { return std::make_shared<Flow>(gameScreen, sf::Vector2f{ 0.f, Flow::XY_DEFAULT_POWER }); });

// init
const sf::Vector2f Flow::DEFAULT_POWER{ 0, 0 };
const float Flow::XY_DEFAULT_POWER = BoardObject::getDefaultSize().x*0.0001f;

Flow::Flow(GameScreen& gameScreen, const sf::Vector2f& flowPower)
	: StaticObject(gameScreen)
{
	setFlow(flowPower);
	init();
}

void Flow::setFlow(const sf::Vector2f& flow)
{
	m_flowPower = flow;
	// TODO fix this:    rotateAnimation(float(std::atan2(-flow.x , -flow.y) * 180.f / M_PI));
}

void Flow::init()
{
	setDrawPriority(DRAW_PRIORITY);
	setAnimation("flow");
	setAnimationFrequency(ANIM_FREQUENCY);
}

