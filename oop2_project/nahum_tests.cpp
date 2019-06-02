#include "~main_tests.h"
#ifdef NAHUM_TESTS

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
void testLifeView();
void testWorld();
#pragma endregion

// -------------- globals & constants -----------
#pragma region globals & constants

#pragma endregion

//--------------  main ---------------------------
void nahum_main()
{
	std::cout << "Hello Nahum World!\n";
	// initialize random seed
	srand(unsigned(time(NULL)));
	try
	{
		//testCleanScreen();
		//testLifeView();
		testWorld();
	}
	catch (const std::exception& ex)
	{
		// Oh No! error...
		ErrorDialog::show(ex.what());
	}
}

void testWorld() {
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	GameScreen gameScreen(window);

	std::shared_ptr<Player> player = std::make_shared<Player>(gameScreen);
	player->setPosition(0, 0);
	gameScreen.getWorld().getBODS().requestAddBO(player);

	std::shared_ptr<MovingObject> m = player;
	AK47 ak(m);
	gameScreen.getWorld().addKeyDownListener([&gameScreen, &ak](sf::Keyboard::Key& keyCode) {
		float offset = 10.f;
		switch (keyCode)
		{
			/*case sf::Keyboard::Key::Left: {
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
			} break;*/
		case sf::Keyboard::Key::Q: {
			gameScreen.getWorld().getCamera().zoom(0.95f);
		} break;
		case sf::Keyboard::Key::W: {
			gameScreen.getWorld().getCamera().zoom(1.05f);
		} break;
		case sf::Keyboard::Key::P: {
			std::cout << "-------------------------------------------------" << std::endl;
			std::cout << gameScreen.getWorld().getBODS().toString() << std::endl;
		} break;
		case sf::Keyboard::Key::Z: {
			ak.useTool();
		} break;
		case sf::Keyboard::Key::R: {
			sf::Vector2f pos = gameScreen.getWorld().getWindow().mapPixelToCoords(sf::Mouse::getPosition(gameScreen.getWorld().getWindow()));
			std::shared_ptr<Wall> wall = std::make_shared<Wall>(gameScreen);
			wall->setPosition(pos);
			gameScreen.getWorld().getBODS().requestAddBO(wall);
		} break;
		}
	});
	gameScreen.getWorld().addClickListener([&gameScreen](View& view) {
		sf::Vector2f pos = gameScreen.getWorld().getWindow().mapPixelToCoords(sf::Mouse::getPosition(gameScreen.getWorld().getWindow()));

		std::shared_ptr<Shark> shark = std::make_shared<Shark>(gameScreen);
		shark->setPosition(pos);
		gameScreen.getWorld().getBODS().requestAddBO(shark);
	});


	gameScreen.getWorld().getBODS().handleRequests();
	gameScreen.getWorld().getBODS().prepareLevel();
	// load level info
	//LevelFileManager lfm;
	//world.loadLevel(lfm.getLevel("testLevel"));


	LevelInfo li;
	li.getLevelChars().resize(100, 100);
	gameScreen.getWorld().loadLevel(li);
	Timer frameTimer;
	frameTimer.start(1, [&gameScreen, &player]() {
		gameScreen.getWorld().getBODS().handleRequests();
		gameScreen.getWorld().getCamera().setCenter(player->getCenter());
	});
	gameScreen.run(frameTimer);

	/*// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	GameScreen gameScreen(window);

	std::shared_ptr<Player> player = std::make_shared<Player>(gameScreen);
	player->setPosition(0, 0);
	gameScreen.getWorld().getBODS().requestAddBO(player);

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
	gameScreen.getWorld().getBODS().handleRequests();
	std::shared_ptr<Shark> shark = std::make_shared<Shark>(gameScreen);
	shark->setPosition(0.07f, 0.01f);
	gameScreen.getWorld().getBODS().requestAddBO(shark);
	/*float distanceFromPlayer = shark->getDistance(player);
	if (distanceFromPlayer <= 2000.f) {
		sf::Vector2f direction = shark->getPosition() - player->getPosition();
		shark->getSpeed().x = direction.x*0.5f;
		shark->getSpeed().y = direction.y*0.5f;
	}
	gameScreen.getWorld().getBODS().prepareLevel();
	gameScreen.getWorld().addClickListener([&gameScreen, player](View& view) {
		sf::Vector2f pos = gameScreen.getWorld().getWindow().mapPixelToCoords(sf::Mouse::getPosition(gameScreen.getWorld().getWindow()));
		
		std::shared_ptr<Shark> shark = std::make_shared<Shark>(gameScreen);
		shark->setPosition(pos);
		shark->addClickListener([&gameScreen, shark, player](View& v) {
			//std::cout << shark->getDistance(player);
		
		});
		gameScreen.getWorld().getBODS().requestAddBO(shark);
	});

	

	// load level info
	//LevelFileManager lfm;
	//world.loadLevel(lfm.getLevel("testLevel"));


	LevelInfo li;
	li.getLevelChars().resize(100, 100);
	gameScreen.getWorld().loadLevel(li);
	Timer frameTimer;
	frameTimer.start(10, [&gameScreen]() {
		gameScreen.getWorld().getBODS().handleRequests();
	});
	gameScreen.run(frameTimer);*/
}

void testLifeView() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(1.f);

	std::shared_ptr<LifeView> lf = std::make_shared<LifeView>(window, 3);
	mainLayout.addView(lf);
	lf->addClickListener([&lf](GUI::View& view) {
		int lives = lf->getNumOfLife();
		++lives;
		lf->setNumOfLife(lives);
	});

	std::shared_ptr<CoinView> cv = std::make_shared<CoinView>(window, 3);
	mainLayout.addView(cv);
	cv->addClickListener([&cv](GUI::View& view) {
		int coins = cv->getNumOfCoins();
		coins--;
		cv->setNumOfCoins(coins);
	});
	std::shared_ptr<GameMenu> gm = std::make_shared<GameMenu>(window);
	mainLayout.addView(gm);

	std::shared_ptr<ToolView> tv = std::make_shared<ToolView>(window);
	mainLayout.addView(tv);
	tv->addClickListener([&tv](GUI::View& view) {
		int ammo = tv->getAmmo();
		ammo--;
		tv->setAmmo(ammo);
	});

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

#endif // NAHUM_TESTS