#include "ChooseLevelScreen.h"
#include "LevelFileManager.h"

ChooseLevelScreen::ChooseLevelScreen(sf::RenderWindow& window, const LevelFileManager& lfm)
	: BaseScreen(window)
{
	initComponents(lfm);
}

void ChooseLevelScreen::addLevelBtClickListener(std::function<void(const std::shared_ptr<GUI::Button>&)> onLevelBtClicked)
{
	for (const auto& levelBt : m_levelsBts) {
		levelBt->addClickListener([onLevelBtClicked, &levelBt](GUI::View& v) {
			onLevelBtClicked(levelBt);
		});
	}
}

string ChooseLevelScreen::toString() const
{
	return "ChooseLevelScreen: { " + BaseClass::toString() + " }";
}

void ChooseLevelScreen::initComponents(const LevelFileManager& lfm)
{
	// init title
	m_title = std::make_shared<GUI::TextView>(getWindow(), "Please choose a level:");
	m_title->setTextColor(sf::Color(21, 1, 84));
	m_title->setTextSize(30);
	m_title->setFont("ARLRDBD");
	m_title->setTextStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);
	addView(m_title, sf::FloatRect(0.f, 0.f, 1.f, 0.2f));

	// init levels layout
	m_levelsBtsLayout = std::make_shared<GUI::VerticalLayout<GUI::Button>>(getWindow());

	// build level buttons
	for (int i = 0; i < lfm.getNumOfLevels(); ++i) {
		const LevelInfo& levelInfo = lfm.getLevel(i);
		std::shared_ptr<GUI::Button> m_levelBt = std::make_shared<GUI::Button>(getWindow(), levelInfo.getName());
		m_levelBt->setTextSize(28);
		m_levelsBts.push_back(m_levelBt);
		m_levelsBtsLayout->addView(m_levelBt);
	}

	addView(m_levelsBtsLayout, sf::FloatRect(0.05f, 0.2f, 0.9f, 0.8f));
}
