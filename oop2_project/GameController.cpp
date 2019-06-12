#include "GameController.h"
#include "AlertDialog.h"

void GameController::run()
{
	// TODO play background music

	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Robbery in the Depths", sf::Style::Fullscreen);

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

	// run
	gameScreen.run([&gameScreen, &player]() {
		gameScreen.getWorld().getBODS().handleRequests();
	});
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
