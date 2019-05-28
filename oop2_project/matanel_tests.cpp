#include "~main_tests.h"
#ifdef MATANEL_TESTS

 //-------------- include section ---------------
#pragma region Includes
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <nlohmann/json.hpp> // JSON library
#include <iostream>
#include "VerticalLayout.h"
#include "ErrorDialog.h"
#include "Button.h"
#include "MainScreen.h"
#include "LevelInfo.h"
#include "LevelFileManager.h"
#include "Matrix.h"
#include "GameObjectInfo.h"
#include "GOIFileParser.h"
#include "GameObjectView.h"
#include "GameObjectsList.h"
#include "BODS.h"
#include "GameScreen.h"
#include "World.h"
#include "Shark.h"
#pragma endregion

 //-------------- libs -------------------------
#pragma region Libs
// for SFML library
#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#pragma comment ( lib , "sfml-system-d.lib" )
#pragma comment ( lib , "sfml-window-d.lib" )
#pragma comment ( lib , "sfml-graphics-d.lib" )
#pragma comment ( lib, "sfml-network-d.lib" )
#pragma comment ( lib, "sfml-audio-d.lib" )
#else
#pragma comment ( lib , "sfml-main.lib" )
#pragma comment ( lib , "sfml-system.lib" )
#pragma comment ( lib , "sfml-window.lib" )
#pragma comment ( lib , "sfml-graphics.lib" )
#pragma comment ( lib, "sfml-network.lib" )
#pragma comment ( lib, "sfml-audio-d.lib" )
#endif
#pragma endregion

//-------------- using section -----------------
#pragma region Usings
using namespace GUI; // for tests only
#pragma endregion

//-------------- declare functions -------------
#pragma region Declarations
void testWorld();
void testBODS();
void testGameObjectView();
void testGameObjectInfo();
void testMatrix();
void testLevelFileManager();
void testLevelInfo();
void testMainScreen();
void testGUI();
void testCleanScreen();
#pragma endregion

// -------------- globals & constants -----------
#pragma region globals & constants

#pragma endregion

//--------------  main ---------------------------
void matanel_main()
{
    std::cout << "Hello Matanel World!\n";
	// initialize random seed
	srand(unsigned (time(NULL)));
	try
	{
		testWorld();
		//testBODS();
		//testGameObjectView();
		//testGameObjectInfo();
		//testMatrix();
		//testLevelFileManager();
		//testLevelInfo();
		//testMainScreen();
		//testGUI();
		//testCleanScreen();
	}
	catch (const std::exception& ex)
	{
		// Oh No! error...
		ErrorDialog::show(ex.what());
	}
}

void testWorld() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	GameScreen gameScreen(window);

	gameScreen.getWorld().addKeyDownListener([&gameScreen](sf::Keyboard::Key& keyCode) {
		float offset = 10.f;
		switch (keyCode)
		{
			case sf::Keyboard::Key::Left: {
				gameScreen.getWorld().getCamera().move(-offset, 0);
			} break;
			case sf::Keyboard::Key::Right: {
				gameScreen.getWorld().getCamera().move(offset, 0);
			} break;
			case sf::Keyboard::Key::Up: {
				gameScreen.getWorld().getCamera().move(0, -offset);
			} break;
			case sf::Keyboard::Key::Down: {
				gameScreen.getWorld().getCamera().move(0, offset);
			} break;
			case sf::Keyboard::Key::Q: {
				gameScreen.getWorld().getCamera().zoom(0.95f);
			} break;
			case sf::Keyboard::Key::W: {
				gameScreen.getWorld().getCamera().zoom(1.05f);
			} break;
		}
	});
	gameScreen.getWorld().addClickListener([&gameScreen](View& view) {
		sf::Vector2f pos = gameScreen.getWorld().getWindow().mapPixelToCoords(sf::Mouse::getPosition(gameScreen.getWorld().getWindow()));

		std::shared_ptr<Shark> shark = std::make_shared<Shark>(gameScreen.getWindow(), gameScreen);
		shark->setPosition(pos);
		shark->setSize(20, 20);
		shark->setParent(gameScreen.getWorld());
		gameScreen.getWorld().getDODS().requestAddBO(shark);
	});

	

	
	// load level info
	//LevelFileManager lfm;
	//world.loadLevel(lfm.getLevel("testLevel"));


	LevelInfo li;
	li.getLevelChars().resize(100, 100);
	gameScreen.getWorld().loadLevel(li);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			gameScreen.getWorld().handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		gameScreen.getWorld().getDODS().handleRequests();

		window.clear();
		gameScreen.getWorld().draw();
		window.display();
	}
}

void testBODS() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	GameScreen gameScreen(window);
	BODS bods;

	for (int i = 0; i < 15; ++i) {
		std::shared_ptr<BoardObject> bo = std::make_shared<BoardObject>(window, gameScreen, i%3);
		bo->setPosition(sf::Vector2f{ float(i),float(i) });
		bo->setSize(sf::Vector2i{ i,i });
		bods.requestAddBO(bo);
	}
	bods.requestAddBO(std::make_shared<Player>(window, gameScreen));

	bods.handleRequests();

	bods.prepareLevel(); // must use this!!!!!!!



	/*for (auto it = bods.getBOs().begin(); it != bods.getBOs().end(); ++it) {
		BoardObject* bo = &**it;
		bods.getAABBTree().updateObject(bo);
		auto ov = bods.getAABBTree().queryOverlaps(bo);
		int ovSize = 0;
		for (auto ovIt = ov.begin(); ovIt != ov.end(); ++ovIt)
			ovSize++;
		std::cout << ovSize << std::endl;
	}*/
	
	//bods.requestRemoveBO(*bods.getBOs().begin());
	//bods.handleRequests();

	std::cout << bods.getPlayer()->toString() << std::endl;
	//std::cout << bods.toString() << std::endl;
}

void testGameObjectView() {
	

	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(1.f);


	std::shared_ptr<GameObjectsList> gol = std::make_shared<GameObjectsList>(window);
	mainLayout.addView(gol);

	gol->addGOVClickListener([](const std::shared_ptr<GameObjectView>& gov) {
		std::cout << gov->getGameObjectInfo().getName() << std::endl;
	});

	std::cout << mainLayout.toString() << std::endl;
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mainLayout.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		mainLayout.draw();
		window.display();
	}
}

void testGameObjectInfo() {
	std::vector<GameObjectInfo> gois = GOIFileParser::parseGOIFile();
	for (GameObjectInfo& goi : gois)
		std::cout << goi.toString() << std::endl;

	//json goiJSON = { { "name", "player" }, { "isUnique", true }, { "specialChar", 'a' } };
	//GameObjectInfo goi = GameObjectInfo::parse(goiJSON);
	//std::cout << goi.toString() << std::endl;
}

void testMatrix() {
	Matrix<int> m(5, 3);
	int i = 0;
	for (auto it = m.begin(); it != m.end(); ++it) {
		(*it) = i;
		i++;
	}

	for (auto it = m.cbegin(); it != m.cend(); ++it) {
		std::cout << it.getCell().toString() << "\n";
	}

	for (auto n : m) {
		std::cout << n << "\n";
	}
}

void testLevelFileManager() {
	LevelFileManager lfm;
	std::cout << lfm.toString() << std::endl;
	/*for (int i = 0; i < lfm.getNumOfLevels(); ++i) {
		const LevelInfo& levelInfo = lfm.getLevel(i);
		std::cout << levelInfo.toString() << std::endl;
	}	*/
	//LevelInfo levelInfo = lfm.getLevel(0);
	//levelInfo.getLevelChars().resize(0, 0);
	//lfm.editLevel(levelInfo);

	//const LevelInfo& levelInfo = lfm.getLevel("level2");
	//lfm.addLevel(lfm.getLevel(0));
}

void testLevelInfo() {
	LevelInfo levelInfo;
	levelInfo.setIndex(2);
	levelInfo.setName("dasds");
	levelInfo.getLevelChars().resize(3, 5);
	Matrix<char>& levelChars = levelInfo.getLevelChars();
	for (int rowNum = 0; rowNum < levelChars.getNumOfRows(); ++rowNum) {
		for (int colNum = 0; colNum < levelChars.getNumOfCols(); ++colNum) {
			Cell cell(rowNum, colNum);
			levelChars[cell] = 'a';
		}
	}	
	std::cout << levelInfo.toString() << std::endl;
	std::cout << levelInfo.toJSON() << std::endl;
	std::cout << "check inversed:" << std::endl;
	std::cout << LevelInfo::parse(levelInfo.toJSON()).toJSON() << std::endl;
}

void testMainScreen() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	MainScreen mainScreen(window);
	mainScreen.run();
}

void testGUI() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(1.f);

	// create buttons
	for (int i = 0; i < 3; i++) {
		std::shared_ptr<Button> bt = std::make_shared<Button>(window, "Button " + std::to_string(i));
		bt->addClickListener([](View& v) {
			v.disable();
		});
		mainLayout.addView(bt);
	}
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mainLayout.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		mainLayout.draw();
		window.display();
	}
}

void testCleanScreen() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(1.f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mainLayout.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		mainLayout.draw();
		window.display();
	}
}

#endif // MATANEL_TESTS