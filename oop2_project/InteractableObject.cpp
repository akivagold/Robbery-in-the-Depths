#include "InteractableObject.h"

InteractableObject::InteractableObject(sf::RenderWindow& window, GameScreen& gameScreen)
	: BoardObject(window, gameScreen), m_damage(0)
{
}
