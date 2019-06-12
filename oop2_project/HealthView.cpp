#include "HealthView.h"

HealthView::HealthView(sf::RenderWindow& window)
	:HorizontalLayout(window)
{
	init();
}

void HealthView::init()
{
	m_barFullPart->getBackground().setColor(sf::Color::Blue);
	m_barEmptyPart->getBackground().setColor(sf::Color::Red);
}
