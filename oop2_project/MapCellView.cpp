#include "MapCellView.h"
#include "Player.h"
#include "Wall.h"
#include "Chest.h"
#include "Shark.h"
#include "Crab.h"
#include "Rubber.h"
#include "ParseLevelException.h"

MapCellView::MapCellView(sf::RenderWindow& window, char ch)
	: GUI::ImageView(window)
{ 
	setChar(ch);
}

void MapCellView::setChar(char ch)
{
	updateImage(ch);
	m_ch = ch;
}

string MapCellView::toString() const
{
	return "MapCellView: { char=" + string(1, m_ch) + ", " + GUI::ImageView::toString() + " }";
}

void MapCellView::updateImage(char ch)
{
	switch (ch)
	{
		case ' ': {
			getImage().setColor(sf::Color::Transparent);
		} break;
		case Player::CHAR: {
			getImage().setTexture("diver");
		} break;
		case Crab::CHAR: {
			getImage().setTexture("crab");
		} break;
		case Wall::CHAR: {
			getImage().setTexture("wall");
		} break;
		case Chest::CHAR: {
			getImage().setTexture("chest");
		} break;
		case Rubber::CHAR: {
			getImage().setTexture("rubber");
		} break;
		case Shark::CHAR: {
			getImage().setTexture("shark");
		} break;
		default:
			throw ParseLevelException("Cannot parse board object with char=" + string(1, ch));
		}
}
