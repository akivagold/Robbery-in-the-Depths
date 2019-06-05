#pragma once
//---- include section ------
#include <string>
#include "View.h"
#include "Timer.h"
#include "SoundManager.h"

//---- using section --------
using std::string;

namespace GUI {
	/*
	 * BaseScreen abstract class
	 */
	template <class ViewType = GUI::View>
	class BaseScreen
		: public ViewType
	{
	public:
		// close screen
		void close() { m_closeFlag = true; }
		// open
		void open() { m_closeFlag = false; }
		// check if screen is closed
		bool isClosed() const { return m_closeFlag; }
		// run the screen and listen to updates with timer
		void run(std::function<void()> onScreenUpdated = nullptr);
		// destructor
		virtual ~BaseScreen() = default;
		// add backgroud root view
		void addBackRootView(const std::shared_ptr<GUI::View>& rootView) { m_backRootViews.push_back(rootView); }
		// convert to string
		virtual string toString() const override { return "BaseScreen: { " + ViewType::toString() + " }"; }
	protected:
		// close flag
		bool m_closeFlag;
		// background root views
		std::vector<std::shared_ptr<GUI::View>> m_backRootViews;
		// constructor
		explicit BaseScreen(sf::RenderWindow& window);
	};

	template<class ViewType>
	BaseScreen<ViewType>::BaseScreen(sf::RenderWindow& window)
		: ViewType(window), m_closeFlag(false)
	{
		ViewType::getBackground().setColor(sf::Color(146, 205, 255));
		ViewType::makeRootView();
		ViewType::addKeyDownListener([this](sf::Keyboard::Key& key) {
			if(key == sf::Keyboard::Escape) {
				close();
				SoundManager::getInterface().playSound("window_close");
			}
		});
	}
	template<class ViewType>
	void BaseScreen<ViewType>::run(std::function<void()> onScreenUpdated)
	{
		while (ViewType::getWindow().isOpen() && !isClosed())
		{
			sf::Event event;
			while (ViewType::getWindow().pollEvent(event))
			{
				for (auto& backRootView : m_backRootViews)
					backRootView->handleEvent(event);
				ViewType::handleEvent(event);
				if (event.type == sf::Event::Closed)
					ViewType::getWindow().close();
			}

			ViewType::getWindow().clear();
			for (auto& backRootView : m_backRootViews)
				backRootView->draw();
			ViewType::draw();
			ViewType::getWindow().display();

			// update timer if needed
			if (onScreenUpdated != nullptr)
				onScreenUpdated();
		}
	}
}
