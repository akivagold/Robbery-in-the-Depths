#include "MapCellView.h"
#include "Player.h"
#include "Wall.h"
#include "Chest.h"
#include "Shark.h"
#include "Crab.h"
#include "Rubber.h"
#include "MachineGun.h"
#include "ParseLevelException.h"
#include "Box.h"

MapCellView::MapCellView(sf::RenderWindow& window)
	: GUI::ImageView(window), m_ch(' ')
{ }

void MapCellView::setChar(const std::vector<GameObjectInfo>& gois, char ch)
{
	updateImage(gois, ch);
	m_ch = ch;
}

string MapCellView::toString() const
{
	return "MapCellView: { char=" + string(1, m_ch) + ", " + GUI::ImageView::toString() + " }";
}

void MapCellView::updateImage(const std::vector<GameObjectInfo>& gois, char ch)
{
	if(ch == ' ')
		getImage().setColor(sf::Color::Transparent);
	else {
		auto it = std::find_if(gois.cbegin(), gois.cend(), [ch](const GameObjectInfo& goi) { return goi.getSpecialChar() == ch; });
		if (it == gois.cend())
			throw ParseLevelException("Cannot find board object with char=" + string(1, ch));
		const GameObjectInfo& goi = *it;
		getImage().setTexture(goi.getName());
	}
}
