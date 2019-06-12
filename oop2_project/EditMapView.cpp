#include "EditMapView.h"

// init
const float EditMapView::ZOOM_CAM_ANIM = 0.02f;
const float EditMapView::MOVE_CAM_ANIM = 4.f;

EditMapView::EditMapView(sf::RenderWindow& window, const std::vector<GameObjectInfo>& gois)
	: BaseClass(window), m_cameraAct(CameraAction::NONE), m_editMode(EditMode::None), m_addChar(' '), m_gois(gois)
{
	initComponents();
}

void EditMapView::importLevelInfo(const LevelInfo& levelInfo)
{
	m_levelInfo = levelInfo;

	// load level
	resize(levelInfo.getLevelChars().getSize());
	for (auto it = levelInfo.getLevelChars().cbegin(); it != levelInfo.getLevelChars().cend(); ++it) {
		const Cell& cell = it.getCell();
		char ch = *it;
		getViewAt(cell)->setChar(m_gois, ch);
	}

	// init cells
	forEach([this](const Cell& cell, const std::shared_ptr<MapCellView>& view) {
		view->addEnterListener([this](View& v) {
			if (m_editMode == EditMode::Add) {
				v.getBackground().setColor(sf::Color::Green);
			}
			else if (m_editMode == EditMode::Remove) {
				v.getBackground().setColor(sf::Color::Red);
			}
		});
		view->addLeaveListener([this](View& v) {
			v.getBackground().setColor(sf::Color::Transparent);
		});
		view->addClickListener([this, &view](View& v) {
			if (m_editMode == EditMode::Add) {
				view->setChar(m_gois, m_addChar);
			}
			else if (m_editMode == EditMode::Remove) {
				view->setChar(m_gois, ' ');
			}
		});
	});
}

const LevelInfo& EditMapView::exportLevelInfo()
{
	// update matrix
	forEach([this](const Cell& cell, const std::shared_ptr<MapCellView>& mapCellView) {
		m_levelInfo.getLevelChars()[cell] = mapCellView->getChar();
	});
	return m_levelInfo;
}

void EditMapView::draw()
{
	m_cameraMoveTimer.checkTimer();
	TableLayout::draw();
}

string EditMapView::toString() const
{
	return "GameEditor: { addChar=" + string(1, m_addChar) + ", cameraAction=" + cameraActToStr(m_cameraAct) + ", " + BaseClass::toString() + " }";
}

string EditMapView::cameraActToStr(CameraAction cameraAct)
{
	string str;
	switch (cameraAct)
	{
		case CameraAction::RIGHT: {
			str = "Right";
		} break;
		case CameraAction::LEFT: {
			str = "Left";
		} break;
		case CameraAction::UP: {
			str = "Up";
		} break;
		case CameraAction::DOWN: {
			str = "Down";
		} break;
		case CameraAction::ZOOM_IN: {
			str = "Zoom in";
		} break;
		case CameraAction::ZOOM_OUT: {
			str = "Zoom out";
		} break;
		case CameraAction::NONE: {
			str = "None";
		} break;
	}
	return str;
}

void EditMapView::initComponents()
{
	makeRootView(true);

	// init self
	getBackground().setColor(sf::Color(146, 205, 255));
	getCamera().zoom(1.1f);

	// listen events
	addKeyDownListener([this](sf::Keyboard::Key key) {
		switch (key) {
			case sf::Keyboard::Key::Up: {
				m_cameraAct = CameraAction::UP;
			} break;
			case sf::Keyboard::Key::Down: {
				m_cameraAct = CameraAction::DOWN;
			} break;
			case sf::Keyboard::Key::Left: {
				m_cameraAct = CameraAction::LEFT;
			} break;
			case sf::Keyboard::Key::Right: {
				m_cameraAct = CameraAction::RIGHT;
			} break;
			case sf::Keyboard::Key::Num1: {
				m_cameraAct = CameraAction::ZOOM_IN;
			} break;
			case sf::Keyboard::Key::Num2: {
				m_cameraAct = CameraAction::ZOOM_OUT;
			} break;
			default:
				break;
		}
	});
	addKeyReleasedListener([this](sf::Keyboard::Key key) {
		switch (key) {
		case sf::Keyboard::Key::Up:
		case sf::Keyboard::Key::Down:
		case sf::Keyboard::Key::Left:
		case sf::Keyboard::Key::Right:
		case sf::Keyboard::Key::Num1:
		case sf::Keyboard::Key::Num2: {
			m_cameraAct = CameraAction::NONE; // stop camera animation
		} break;
		}
	});

	// create movement timer
	m_cameraMoveTimer.start(ANIM_REFRESH_TIME, [this] {
		switch (m_cameraAct)
		{
		case CameraAction::RIGHT: {
			getCamera().move(MOVE_CAM_ANIM, 0);
		} break;
		case CameraAction::LEFT: {
			getCamera().move(-MOVE_CAM_ANIM, 0);
		} break;
		case CameraAction::UP: {
			getCamera().move(0, -MOVE_CAM_ANIM);
		} break;
		case CameraAction::DOWN: {
			getCamera().move(0, MOVE_CAM_ANIM);
		} break;
		case CameraAction::ZOOM_IN: {
			getCamera().zoom(1 - ZOOM_CAM_ANIM);
		} break;
		case CameraAction::ZOOM_OUT: {
			getCamera().zoom(1 + ZOOM_CAM_ANIM);
		} break;
		}
	});
}
