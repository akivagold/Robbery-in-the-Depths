#pragma once
//---- include section ------
#include "View.h"
#include "Timer.h"
#include "TextureInfo.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace GUI {
/*
 * AnimationView class
 */
class AnimationView :
	public GUI::View
{
public:
	// constructor
	explicit AnimationView(sf::RenderWindow& window);
	// copy constructor
	AnimationView(const AnimationView& anotherAnimView);
	// set animation
	void setAnimation(const string& animName);
	// clear animation images
	void clearAnimImages();
	// check if have animation
	bool isHaveAnimation() const { return m_textureInfo != nullptr; }
	// set animation frequency - get time in milliseconds to one frame
	void setAnimationFrequency(int frameMillis);
	// stop animation
	void stopAnimation() { m_timer.stop(); }
	// draw
	virtual void draw() override;
	// flip
	void flipAnimation();
	// check if animation is flipped
	bool isFlipped() const { return m_isFlipped; }
	// convert to string
	virtual string toString() const override;
	// set transparency (number from 0 to 255)
	void setTransparency(sf::Uint32 transparency);
	// get transparency
	sf::Uint32 getTransparency() const { return m_sprite.getColor().a; }
protected:
	// update components
	virtual void updateComponents();
	// get sprite
	sf::Sprite& getSprite() { return m_sprite; }
private:
	// current sprite
	sf::Sprite m_sprite;
	// current texture
	TextureInfo* m_textureInfo;
	// current image index
	int m_currentImageIndex;
	// timer for frames
	Timer m_timer;
	// is flipped
	bool m_isFlipped;
	// set current image
	void setCurrentImage(int index);
	// update sprite
	void updateSprite();
};
}
