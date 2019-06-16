#pragma once
//---- include section ------
#include "TextView.h"
#include <string>
#include <queue>
#include "StopWatch.h"

//---- using section --------
using std::string;

/*
 * GameAnimText class
 */
class GameAnimText
	: public GUI::TextView
{
public:
	// constructor
	explicit GameAnimText(sf::RenderWindow& window);
	// show text
	void showText(const string& text);
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override { return "GameAnimText: { " + GUI::TextView::toString() + " }"; }
private:
	// time to text
	static const int SHOW_TEXT_TIME = 2000;
	// wait texts
	std::queue<string> m_waitTexts;
	// text stop watch
	StopWatch m_textSW;
	// flag for ready to show next text
	bool m_readyToNext;
	// init
	void init();
	// check if can show next text
	bool canShowNextText() const { return (!m_waitTexts.empty() && !m_textSW.isActive()); }
	// show next text
	void showNextText();
	// event on end show text
	void onEndShowText();
	// disable setText
	using GUI::TextView::setText;
};

