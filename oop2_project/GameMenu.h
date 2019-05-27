#pragma once
//---- include section ------
#include <string>
#include "HorizontalLayout.h"
#include "CoinView.h"
#include "LifeView.h"
#include "ToolView.h"
#include "TextView.h"

//---- using section --------
using std::string;
/*
 * GameMenu class
 */
class GameMenu :
	public GUI::HorizontalLayout<GUI::View>
{
public:
	// constructor
	explicit GameMenu(sf::RenderWindow& window);
	// get restart button
	const std::shared_ptr<CoinView>& getCoinView() const { return m_coinView; }
	// get exit button
	const std::shared_ptr<LifeView>& getLifeView() const { return m_lifeView; }
	// get turn button
	const std::shared_ptr<ToolView>& getToolView() const { return m_toolView; }
	// get level num
	const std::shared_ptr<GUI::TextView>& getLevelNumTV() { return m_levelNumTV; }
	// convert to string
	virtual string toString() const override;
private:
	// coin view
	std::shared_ptr<CoinView> m_coinView;
	// tool view
	std::shared_ptr<ToolView> m_toolView;
	// level num
	std::shared_ptr<GUI::TextView> m_levelNumTV;
	// life view
	std::shared_ptr<LifeView> m_lifeView;
	// init components
	void initComponents();
};


