//---- include section ------
#include "AnimationView.h"
#include "TextureManager.h"
#include "BoardObject.h"
#include <iostream>

GUI::AnimationView::AnimationView(sf::RenderWindow& window)
	: View(window), m_currentImageIndex(0), m_textureInfo(nullptr), m_isFlipped(false)
{}

GUI::AnimationView::AnimationView(const AnimationView& anotherAnimView)
	: View(anotherAnimView) // copy the view part of another animation view
{
	// copy fields
	m_textureInfo = anotherAnimView.m_textureInfo;
	m_timer = anotherAnimView.m_timer;
	m_currentImageIndex = anotherAnimView.m_currentImageIndex;
	m_sprite = anotherAnimView.m_sprite;

	if (m_timer.getInterval() > 0) {
		// update animation frequency
		setAnimationFrequency(m_timer.getInterval());
	}
}

void GUI::AnimationView::setAnimation(const string& animName)
{
	m_textureInfo = &const_cast<TextureInfo&>(TextureManager::getInterface().getTextureInfo(animName));
	m_sprite.setTexture(m_textureInfo->getTexture());
	setCurrentImage(0);
}

void GUI::AnimationView::clearAnimImages()
{
	setCurrentImage(0);
	m_textureInfo = nullptr;
}

void GUI::AnimationView::setAnimationFrequency(int frameMillis)
{
	// update timer
	m_timer.start(frameMillis, [this]() {
		if (this->isHaveAnimation()) {
			if (this->m_currentImageIndex + 1 == this->m_textureInfo->getNumOfImages()) {
				this->setCurrentImage(0);
			}
			else {
				this->setCurrentImage(this->m_currentImageIndex + 1);
			}
		}
	});
}

void GUI::AnimationView::draw()
{
	View::draw();

	if (isShow() && isHaveAnimation() && (m_textureInfo->getNumOfImages() > 0)) {
		// check timer before get current image
		m_timer.checkTimer();
		// draw current image
		getWindow().draw(m_sprite);
	}
}

void GUI::AnimationView::flipAnimation()
{
	m_isFlipped = !m_isFlipped;
	updateComponents();
}

string GUI::AnimationView::toString() const
{
	string str = "AnimationView: { ";
	if (isHaveAnimation()) {
		str += "numOfImages = " + std::to_string(m_textureInfo->getNumOfImages()) + ", ";
	}
	str += m_timer.toString() + ", " + View::toString() + " }";
	return str;
}

void GUI::AnimationView::rotateAnimation(float relative_degrees)
{
	double xSize = getSize().x;
	double ySize = getSize().y;
	// find radius
	double radius = std::sqrt(std::pow(ySize, 2) + std::pow(xSize, 2)) / 2;
	// find real degree rotation
	double degreeFix = std::atan2(xSize , ySize) * 180 / M_PI;
	// find original center
	double position_x = std::cos((360 - (90 - degreeFix)) * M_PI / 180) * radius;
	double position_y = std::sin((360 - (90 - degreeFix)) * M_PI / 180) * radius;
	double degrees = relative_degrees - (90 - degreeFix);
	// find current center
	double x = std::cos(degrees * M_PI / 180) * radius;
	double y = std::sin(degrees * M_PI / 180) * radius;
	// fix after rotation
	m_sprite.setOrigin(float(y - position_y), -float(x - position_x));
	// rotate anti clockwise
	m_sprite.rotate(-relative_degrees);
	
}

void GUI::AnimationView::updateComponents()
{
	View::updateComponents();
	updateSprite();
}

void GUI::AnimationView::setCurrentImage(int index)
{
	m_currentImageIndex = index;
	updateSprite();
}

void GUI::AnimationView::updateSprite()
{
	if (isHaveAnimation()) {
		// calculate area
		int numOfRow = m_currentImageIndex / m_textureInfo->getNumOfCols();
		int numOfCol = m_currentImageIndex % m_textureInfo->getNumOfCols();

		float pixelsPerRow = (float)m_textureInfo->getTexture().getSize().y / (float)m_textureInfo->getNumOfRows();
		float pixelsPerCol = (float)m_textureInfo->getTexture().getSize().x / (float)m_textureInfo->getNumOfCols();
		sf::IntRect imageBounds((int)pixelsPerCol*numOfCol, (int)pixelsPerRow*numOfRow, (int)pixelsPerCol, (int)pixelsPerRow);
		// update sprite
		m_sprite.setTextureRect(imageBounds);
		m_sprite.setPosition(getPosition());
		float scaleX = (float)getBound().width / pixelsPerCol;
		float scaleY = (float)getBound().height / pixelsPerRow;

		if (m_isFlipped) {
			scaleX = -scaleX;
			m_sprite.setPosition(getPosition().x + getSize().x, getPosition().y);
		}
		m_sprite.setScale(scaleX, scaleY);
	}
}
