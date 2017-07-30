#include "StateScreenTitle.h"
#include "Draw/DrawableContainer.h"
#include "Graphic/System/GraphicSystem.h"
#include "GUI/Components/Concrete/Button.h"
#include "GUI/Components/Concrete/Label.h"
#include "GUI/Components/Concrete/Image.h"
#include "StatePongGame.h"

const std::string& screenTitleTheme = "." FILE_SEPARATOR "Resources" FILE_SEPARATOR "Menu" FILE_SEPARATOR "start_screen_theme" FILE_SEPARATOR;

StateScreenTitle::StateScreenTitle(StateData & data, ska::StateHolder & sh):
	StateBase(data.m_entityManager, data.m_eventDispatcher, sh),
	SubObserver(std::bind(&StateScreenTitle::onGameEvent, this, std::placeholders::_1), static_cast<ska::Observable<ska::GameEvent>&>(data.m_eventDispatcher)),
	m_gui(data.m_eventDispatcher),
	m_pressStartWindow(nullptr) {
	
	auto& backgroundImageWindow = m_gui.addWindow<ska::WindowIG<>>("backgroundImageWindow", ska::Rectangle{ 0,0,0,0 }, "");
	m_backgroundImage = &backgroundImageWindow.addWidget<ska::Image>(screenTitleTheme + "background.png", ska::Point<int>(), false, nullptr);

	m_pressStartWindow = &m_gui.addWindow<ska::DynamicWindowIG<>>("screenTitleWindow", ska::Rectangle{ 0, 0, 390, 50 }, screenTitleTheme + "menu");
	ska::Point<int> buttonPos(3, 1);
	m_pressStartWindow->addWidget<ska::Button>(buttonPos, screenTitleTheme + "button", nullptr, [&](ska::Widget *, ska::ClickEvent& ce) {
		if (ce.getState() == ska::MOUSE_RELEASE) {
			//std::cout << "lol" << std::endl;
			makeNextState<StatePongGame>(m_backgroundImage->getBox().w, m_backgroundImage->getBox().h);
		}
	});
	m_pressStartWindow->addWidget<ska::Label>("Play game", 36, ska::Point<int>(buttonPos.x + 120, buttonPos.y + 10)).setFontColor(255, 255, 255, 255);
}

void StateScreenTitle::onGraphicUpdate(unsigned int, ska::DrawableContainer& container) {
	container.addHead(m_gui);
}

void StateScreenTitle::onEventUpdate(unsigned int ellapsedTime) {
	m_gui.refresh(ellapsedTime);
}

bool StateScreenTitle::onGameEvent(ska::GameEvent & ge) const{
	ska::Point<int> newPos(ge.windowWidth / 2 - m_pressStartWindow->getBox().w / 2, ge.windowHeight - m_pressStartWindow->getBox().h * 1.5);
	m_pressStartWindow->move(newPos);
	m_backgroundImage->setWidth(ge.windowWidth);
	m_backgroundImage->setHeight(ge.windowHeight);
	return true;
}
