#include "Cop.h"
#include "Flow.h"

Cop::Cop(GameScreen& gameScreen, int numOfLife)
	: NPC(gameScreen, numOfLife)
{
	// TODO setDamge();
}

void Cop::onCollide(Flow* flow)
{
	setExternaAlcceleration(flow->getFlowPower());
}
