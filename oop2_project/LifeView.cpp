#include "LifeView.h"




LifeView::LifeView(sf::RenderWindow & window, int numOfLife)
	: HorizontalLayout(window)
{
	init();
	setNumOfLife(numOfLife);
}

void LifeView::setLife(int numOfLife)
{
	removeAllViews();
	for (int i = 0; i < numOfLife; ++i) {
		std::shared_ptr<GUI::ImageView> lifeImage = crateLifeImage();
		addView(lifeImage);
	}
}

void LifeView::setNumOfLife(int numOfLife)
{
	checkLegalLife(numOfLife);
	m_numOfLife = numOfLife;
	setLife(numOfLife);
}

string LifeView::toString() const
{
	return "LifeView: { " + HorizontalLayout::toString() + " }";
}

std::shared_ptr<GUI::ImageView> LifeView::crateLifeImage()
{
	std::shared_ptr<GUI::ImageView> lifeImage = std::make_shared<GUI::ImageView>(getWindow());
	lifeImage->getImage().setTexture("life");
	return lifeImage;
}

void LifeView::checkLegalLife(int numOfLife) const
{
	if (numOfLife < 0)
		throw std::out_of_range("Num of life - " + std::to_string(numOfLife) + " - is illegal");
}

void LifeView::init()
{
	getBorder().setColor(sf::Color::Black);
}
