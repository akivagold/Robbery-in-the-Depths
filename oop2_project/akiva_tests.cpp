#include "~main_tests.h"
#ifdef AKIVA_TESTS

//-------------- include section ---------------
#pragma region Includes
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <nlohmann/json.hpp> // JSON library
#include <iostream>
#include "VerticalLayout.h"
#include "ErrorDialog.h"
#include "LifeView.h"
#include "CoinView.h"
#include "ToolView.h"
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
#include "GameMenu.h"
#include "Wall.h"
#include "AK47.h"
#include "Rubber.h"
#include "Crab.h"
#include "Chest.h"
#include "Flow.h"
#include "EditMapView.h"
#include "EditMenu.h"
#include "EditScreen.h"
#include "MachineGun.h"
#include "GameCamera.h"
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
void testCleanScreen();
void testWorld();
#pragma endregion

// -------------- globals & constants -----------
#pragma region globals & constants

#pragma endregion

//--------------  main ---------------------------
void akiva_main()
{
	std::cout << "Hello Akiva World!\n";
	// initialize random seed
	srand(unsigned(time(NULL)));
	try
	{
		testWorld();
	}
	catch (const std::exception& ex)
	{
		// Oh No! error...
		ErrorDialog::show(ex.what());
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


/*void testWorld() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	GameScreen gameScreen(window);

	std::shared_ptr<Player> player = std::make_shared<Player>(gameScreen);
	player->setPosition(0,0);
	gameScreen.getWorld().getBODS().requestAddBO(player);

	std::shared_ptr<Flow> flow = std::make_shared<Flow>(gameScreen);
	flow->setSize(BoardObject::getDefaultSize().x * 4, BoardObject::getDefaultSize().y * 4);;
	flow->setPosition(BoardObject::getDefaultSize().x * 4.f, BoardObject::getDefaultSize().y * 4.f);
	flow->setFlowPower(sf::Vector2f(0.0025f, 0.f));
	gameScreen.getWorld().getBODS().requestAddBO(flow);

	std::shared_ptr<Flow> flow1 = std::make_shared<Flow>(gameScreen);
	flow1->setSize(BoardObject::getDefaultSize().x * 4, BoardObject::getDefaultSize().y * 4);;
	flow1->setPosition(BoardObject::getDefaultSize().x * 12.f, BoardObject::getDefaultSize().y * 4.f);
	flow1->setFlowPower(sf::Vector2f(0.f, 0.0025f));
	gameScreen.getWorld().getBODS().requestAddBO(flow1);

	std::shared_ptr<Flow> flow2 = std::make_shared<Flow>(gameScreen);
	flow2->setSize(BoardObject::getDefaultSize().x * 4, BoardObject::getDefaultSize().y * 4);;
	flow2->setPosition(BoardObject::getDefaultSize().x * 4.f, BoardObject::getDefaultSize().y * 12.f);
	flow2->setFlowPower(sf::Vector2f(0.f, -0.0025f));
	gameScreen.getWorld().getBODS().requestAddBO(flow2);

	std::shared_ptr<Flow> flow3 = std::make_shared<Flow>(gameScreen);
	flow3->setSize(BoardObject::getDefaultSize().x * 4, BoardObject::getDefaultSize().y * 4);;
	flow3->setPosition(BoardObject::getDefaultSize().x * 12.f, BoardObject::getDefaultSize().y * 12.f);
	flow3->setFlowPower(sf::Vector2f(-0.0025f, 0.f));
	gameScreen.getWorld().getBODS().requestAddBO(flow3);


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

		std::shared_ptr<Shark> shark = std::make_shared<Shark>(gameScreen);
		shark->setPosition(pos);
		shark->addClickListener([&gameScreen, shark](View& v) {
			// TODO
		});
		gameScreen.getWorld().getBODS().requestAddBO(shark);
	});



	gameScreen.getWorld().getBODS().handleRequests();
	gameScreen.getWorld().getBODS().prepareLevel();
	// load level info
	//LevelFileManager lfm;
	//world.loadLevel(lfm.getLevel("testLevel"));


	//LevelInfo li;
	//li.getLevelChars().resize(100, 100);
	//gameScreen.loadLevel(li);
	Timer frameTimer;
	frameTimer.start(10, [&gameScreen]() {
		gameScreen.getWorld().getBODS().handleRequests();
	});
	gameScreen.run(frameTimer);
}
*/
void testWorld() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Screen");

	GameScreen gameScreen(window);

	// load level info
	LevelFileManager lfm;
	const LevelInfo& levelInfo = lfm.getLevel("akiva map");
	gameScreen.loadLevel(levelInfo);

	// get player
	std::shared_ptr<Player> player = gameScreen.getWorld().getBODS().getPlayer();
	//player->addTool(std::make_shared<AK47>(player.get()));
	//player->getCurrTool()->setInfLimit();

	gameScreen.getWorld().addKeyDownListener([&gameScreen, &player](sf::Keyboard::Key& keyCode) {
		float offset = 10.f;
		sf::Vector2f mousePos = gameScreen.getWorld().getWindow().mapPixelToCoords(sf::Mouse::getPosition(gameScreen.getWorld().getWindow()));
		switch (keyCode)
		{
		case sf::Keyboard::Key::U: {
			player->setTransparency(player->getTransparency() - 10);
		} break;
		case sf::Keyboard::Key::Num2: {
			gameScreen.getWorld().getCamera().zoom(0.95f);
		} break;
		case sf::Keyboard::Key::Num1: {
			gameScreen.getWorld().getCamera().zoom(1.05f);
		} break;
		case sf::Keyboard::Key::P: {
			std::cout << "-------------------------------------------------" << std::endl;
			std::cout << gameScreen.getWorld().getBODS().toString() << std::endl;
		} break;
		case sf::Keyboard::Key::W: {
			std::shared_ptr<Wall> wall = std::make_shared<Wall>(gameScreen);
			wall->setPosition(mousePos);
			gameScreen.getWorld().getBODS().requestAddBO(wall);
		} break;
		case sf::Keyboard::Key::C: {
			std::shared_ptr<Crab> crab = std::make_shared<Crab>(gameScreen);
			crab->setPosition(mousePos);
			gameScreen.getWorld().getBODS().requestAddBO(crab);
		} break;
		case sf::Keyboard::Key::T: {
			std::shared_ptr<Chest> chest = std::make_shared<Chest>(gameScreen);
			chest->setPosition(mousePos);
			gameScreen.getWorld().getBODS().requestAddBO(chest);
		} break;
		case sf::Keyboard::F: {
			std::shared_ptr<Flow> flow = std::make_shared<Flow>(gameScreen);
			flow->setSize(BoardObject::getDefaultSize().x * 4, BoardObject::getDefaultSize().y * 4);
			flow->setPosition(mousePos);
			flow->setFlow(sf::Vector2f(0.00025f, 0.f));
			gameScreen.getWorld().getBODS().requestAddBO(flow);
		} break;
		case sf::Keyboard::G: {
			std::shared_ptr<Flow> flow = std::make_shared<Flow>(gameScreen);
			flow->setSize(BoardObject::getDefaultSize().x * 4, BoardObject::getDefaultSize().y * 4);
			flow->setPosition(mousePos);
			flow->setFlow(sf::Vector2f(-0.00025f, 0.f));
			gameScreen.getWorld().getBODS().requestAddBO(flow);
		} break;
		case sf::Keyboard::H: {
			std::shared_ptr<Flow> flow = std::make_shared<Flow>(gameScreen);
			flow->setSize(BoardObject::getDefaultSize().x * 4, BoardObject::getDefaultSize().y * 4);
			flow->setPosition(mousePos);
			flow->setFlow(sf::Vector2f(0.f, 0.00025f));
			gameScreen.getWorld().getBODS().requestAddBO(flow);
		} break;
		case sf::Keyboard::J: {
			std::shared_ptr<Flow> flow = std::make_shared<Flow>(gameScreen);
			flow->setSize(BoardObject::getDefaultSize().x * 4, BoardObject::getDefaultSize().y * 4);
			flow->setPosition(mousePos);
			flow->setFlow(sf::Vector2f(0.f, -0.00025f));
			gameScreen.getWorld().getBODS().requestAddBO(flow);
		} break;
		case sf::Keyboard::R: {
			std::shared_ptr<Rubber> rubber = std::make_shared<Rubber>(gameScreen);
			rubber->setPosition(mousePos);
			gameScreen.getWorld().getBODS().requestAddBO(rubber);
		} break;
		case sf::Keyboard::B: {
			std::shared_ptr<MachineGun> gunTrap = std::make_shared<MachineGun>(gameScreen, MovingObject::Direction::UP);
			std::shared_ptr<HotWeapon> ak = std::make_shared<AK47>(gunTrap.get());
			ak->setInfLimit();
			gunTrap->setWeapon(ak);
			gunTrap->setPosition(mousePos);
			gameScreen.getWorld().getBODS().requestAddBO(gunTrap);
		} break;
		case sf::Keyboard::N: {
			std::shared_ptr<MachineGun> gunTrap = std::make_shared<MachineGun>(gameScreen, MovingObject::Direction::RIGHT);
			std::shared_ptr<HotWeapon> ak = std::make_shared<AK47>(gunTrap.get());
			ak->setInfLimit();
			gunTrap->setWeapon(ak);
			gunTrap->setPosition(mousePos);
			gameScreen.getWorld().getBODS().requestAddBO(gunTrap);
		} break;
		}
	});
	gameScreen.getWorld().addClickListener([&gameScreen](View& view) {
		sf::Vector2f pos = gameScreen.getWorld().getWindow().mapPixelToCoords(sf::Mouse::getPosition(gameScreen.getWorld().getWindow()));

		std::shared_ptr<Shark> shark = std::make_shared<Shark>(gameScreen);
		shark->setPosition(pos);
		gameScreen.getWorld().getBODS().requestAddBO(shark);
	});
	/*
	gameScreen.getWorld().getCamera().setViewport(sf::FloatRect(0.f, 0.2f, 1.f, 0.8f));
	gameScreen.getWorld().getCamera().setCenter(sf::Vector2f(gameScreen.getWorld().getCenter()));
	sf::Clock clock;
	GameCamera gameCamera( gameScreen, player, clock);
	*/
	gameScreen.run([&gameScreen]() {
		gameScreen.getWorld().getBODS().handleRequests();
		//gameCamera.updateCamera();
	});
}
#endif // AKIVA_TESTS