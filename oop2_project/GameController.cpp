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
	MainScreen mainScreen(window);
	mainScreen.getExitBt()->addClickListener([&mainScreen](GUI::View& v) {
		mainScreen.close();
	});
	mainScreen.getEditBt()->addClickListener([this](GUI::View& v) {
		// TODO open choose level screen
		LevelFileManager lfm;
		const LevelInfo& levelInfo = lfm.getLevel("matanel map");
		runEditScreen(v.getWindow(), lfm, levelInfo);
	});
	mainScreen.getStartBt()->addClickListener([this](GUI::View& v) {

		// TODO load level of player from file
		
		LevelFileManager lfm;
		const LevelInfo& levelInfo = lfm.getLevel("matanel map");
		runGameScreen(v.getWindow(), levelInfo);
	});
	mainScreen.run();
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
		gameScreen.getWorld().getCamera().setCenter(player->getCenter());
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
