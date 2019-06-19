//---- include section ------
#include "AnimationView.h"
#include "TextureManager.h"
#include "BoardObject.h"
#include <iostream>

GUI::AnimationView::AnimationView(sf::RenderWindow& window)
	: View(window), m_currentImageIndex(0), m_textureInfo(nullptr), m_isFlipped(false)
{ }

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

void GUI::AnimationView::setTransparency(sf::Uint32 transparency)
{
	sf::Color newColor = m_sprite.getColor();
	newColor.a = transparency;
	m_sprite.setColor(newColor);
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

/* an other option for rotate
void GUI::AnimationView::rotateViewAt(sf::Vector2f coord, sf::Sprite& sprite, float rotation)
{
	const sf::Vector2f offset{ coord - sf::Vector2f(sprite.getPosition() - (sf::Vector2f(sprite.getTexture()->getSize())/2.f)) };
	const float rotationInRadians{ rotation * 3.141592653f / 180.f };
	const float sine{ std::sin(rotationInRadians) }; 
	const float cosine{ std::cos(rotationInRadians) }; 
	const sf::Vector2f rotatedOffset{ cosine * offset.x - sine * offset.y, sine * offset.x + cosine * offset.y };
	sprite.rotate(rotation);
	sprite.move(offset - rotatedOffset);
}
*/
