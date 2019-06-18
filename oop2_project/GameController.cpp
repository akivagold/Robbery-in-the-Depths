#include "GameController.h"
#include "AlertDialog.h"
#include "LoseScreen.h"

void GameController::run()
{
	// TODO play background music

	// create window
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window;
	window.create(sf::VideoMode(1000, 500, desktop.bitsPerPixel), "Robbery in the Depths", sf::Style::Fullscreen);

	// TODO set game icon at window

	runMainScreen(window);
}

string GameController::toString() const
{
	return "GameController: { }";
}

void GameController::runMainScreen(sf::RenderWindow& window)
{
	// read levels
	LevelFileManager lfm;

	MainScreen mainScreen(window);
	mainScreen.getExitBt()->addClickListener([&mainScreen](GUI::View& v) {
		mainScreen.close();
	});
	mainScreen.getEditBt()->addClickListener([this, &lfm](GUI::View& v) {
		runChooseLevelScreen(v.getWindow(), lfm, [&v, this, &lfm](const LevelInfo& levelInfo) {
			runEditScreen(v.getWindow(), lfm, levelInfo);
		});
	});
	mainScreen.getStartBt()->addClickListener([this, &lfm](GUI::View& v) {
		runChooseLevelScreen(v.getWindow(), lfm, [&v, this](const LevelInfo& levelInfo) {
			runGameScreen(v.getWindow(), levelInfo);
		});	
	});
	mainScreen.run();
}

void GameController::runChooseLevelScreen(sf::RenderWindow& window, LevelFileManager& lfm, std::function<void(const LevelInfo&)> onLevelChoosed)
{
	ChooseLevelScreen chooseLevelScreen(window, lfm);
	chooseLevelScreen.addLevelBtClickListener([onLevelChoosed, &lfm, &chooseLevelScreen](const std::shared_ptr<GUI::Button>& levelBt) {
		string levelName = levelBt->getText();
		const LevelInfo& levelInfo = lfm.getLevel(levelName);
		onLevelChoosed(levelInfo);
		chooseLevelScreen.close();
	});
	chooseLevelScreen.run();
}

void GameController::runGameScreen(sf::RenderWindow& window, const LevelInfo& levelInfo)
{
	GameScreen gameScreen(window);

	// load level info
	gameScreen.loadLevel(levelInfo);

	// get player
	std::shared_ptr<Player> player = gameScreen.getWorld().getBODS().getPlayer();

	player->setOnDieListener([&gameScreen] {
		gameScreen.getGameAnimText()->showText(GameAnimText::TextInfo("You lose", sf::Color::Red));
	});
	player->setOnVanishListener([this, &gameScreen, &levelInfo] {
		runLoseScreen(gameScreen.getWindow(), levelInfo);
		gameScreen.close();
	});
	player->setOnComeELListener([this, &gameScreen, &player] {
		runWinScreen(gameScreen.getWindow(), player->getNumOfScore());
		gameScreen.close();
	});

	// run
	gameScreen.run([&gameScreen, &player]() {
		gameScreen.getWorld().getBODS().handleRequests();
	});
}

void GameController::runWinScreen(sf::RenderWindow& window, int score)
{
	WinScreen winScreen(window, score);
	winScreen.getBackToMenuBT()->addClickListener([&winScreen](GUI::View& v) {
		winScreen.close();
	});
	winScreen.run();
}

void GameController::runLoseScreen(sf::RenderWindow& window, const LevelInfo& fromLevelInfo)
{
	LoseScreen loseScreen(window);
	loseScreen.getBackToMenuBT()->addClickListener([&loseScreen](GUI::View& v) {
		loseScreen.close();
	});
	loseScreen.getRestartBT()->addClickListener([this, &fromLevelInfo, &loseScreen](GUI::View& v) {
		runGameScreen(v.getWindow(), fromLevelInfo);
		loseScreen.close();
	});
	loseScreen.run();
}

void GameController::runEditScreen(sf::RenderWindow& window, LevelFileManager& levelFileManager, const LevelInfo& levelInfo)
{
	// create editor
	EditScreen editScreen(window);

	// load level info
	editScreen.getEditMapView()->importLevelInfo(levelInfo);

	editScreen.getEditMenu()->getExitButton()->addClickListener([&editScreen](GUI::View& v) {
		editScreen.close();
	});
	editScreen.getEditMenu()->getSaveButton()->addClickListener([&editScreen, &levelFileManager](GUI::View& v) {
		const LevelInfo& levelInfo = editScreen.getEditMapView()->exportLevelInfo();
		levelFileManager.editLevel(levelInfo);
		GUI::AlertDialog::show("Level saved!", "The level saved successfuly!", "OK");
	});
	editScreen.getEditMapView()->forEach([&editScreen](const Cell& cell, const std::shared_ptr<MapCellView>& mapCellView) {
		mapCellView->addEnterListener([&editScreen, cell](GUI::View& v) {
			editScreen.getEditMenu()->setCurrentCell(cell);
		});
	});
	editScreen.getGameObjs()->addGOVClickListener([&editScreen](const std::shared_ptr<GameObjectView>& gov) {
		editScreen.getEditMapView()->setEditMode(EditMapView::EditMode::Add);
		editScreen.getEditMapView()->setAddChar(gov->getGOI().getSpecialChar());
	});
	editScreen.getEditMenu()->getDeleteButton()->addClickListener([&editScreen](GUI::View& view) {
		editScreen.getEditMapView()->setEditMode(EditMapView::EditMode::Remove);
	});

	editScreen.run();
}
