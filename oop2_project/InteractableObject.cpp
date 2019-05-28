#include "InteractableObject.h"

InteractableObject::InteractableObject(GameScreen& gameScreen)
	: BoardObject(gameScreen), m_damage(0)
{
}
