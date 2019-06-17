#include "GameAnimText.h"

GameAnimText::GameAnimText(sf::RenderWindow& window)
	: GUI::TextView(window), m_readyToNext(false)
{
	init();
}

void GameAnimText::showText(const TextInfo& textInfo)
{
	m_waitTexts.push(textInfo);
	if(canShowNextText())
		showNextText();
}

void GameAnimText::draw()
{
	if (m_readyToNext) {
		showNextText();
		m_readyToNext = false;
	}
	m_textSW.checkStopWatch();	
	GUI::TextView::draw();
}

void GameAnimText::init()
{
	setTextColor(sf::Color(0, 42, 58));
	setTextSize(35);
	setTextStyle(sf::Text::Style::Bold);
	setFont("BERNHC");
}

void GameAnimText::showNextText()
{
	// set text
	TextInfo& textInfo = m_waitTexts.front();
	setText(textInfo.m_text);
	setTextColor(textInfo.m_color);
	m_waitTexts.pop();
	// listen to end
	m_textSW.start(SHOW_TEXT_TIME, [this]() { onEndShowText(); });
}

void GameAnimText::onEndShowText()
{
	if (!m_waitTexts.empty())
		m_readyToNext = true;
	else
		setText("");
}
