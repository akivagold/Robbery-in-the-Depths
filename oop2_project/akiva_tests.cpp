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
		testCleanScreen();
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

#endif // AKIVA_TESTS