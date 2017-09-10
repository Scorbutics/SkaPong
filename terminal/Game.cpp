#include "Game.h"
#include "Inputs/KeyboardInputGUIContext.h"
#include "StateScreenTitle.h"
#include "Draw/SDLFont.h"
#include "KeyboardInputTerminalContext.h"

const Uint32 Game::COLOR_PALET[] = {
	0xFD2567FF,
	0x51007BFF,
	0x340BBFFF,
	0xBB0572FF,
	0x700776FF,
	0x8A76BEFF,
	0xEB725BFF,
	0xFE9825FF,
	0x3224E4FF
};

ska::GameApp& ska::GameApp::get() {
	static Game wgc;
	wgc.init();
	return wgc;
}

void Game::init() {
	/* Configure inputs types */
	addInputContext<KeyboardInputTerminalContext>(ska::EnumContextManager::CONTEXT_MAP);
	addInputContext<ska::KeyboardInputGUIContext>(ska::EnumContextManager::CONTEXT_GUI);

	auto renderer = ska::SDLRenderer::getDefaultRenderer();
	renderer->setRenderColor(ska::Color(0, 0, 0, 255));

	ska::GUI::MENU_DEFAULT_THEME_PATH = "." FILE_SEPARATOR "Resources" FILE_SEPARATOR "Menu" FILE_SEPARATOR "start_screen_theme" FILE_SEPARATOR;
	ska::SDLFont::DEFAULT_FONT_FILE = "." FILE_SEPARATOR "Resources" FILE_SEPARATOR "Fonts" FILE_SEPARATOR "8bit16.ttf";
	
	m_gui = std::make_unique<GUI>(m_eventDispatcher);

	navigateToState<StateScreenTitle>(*m_gui.get());
}

int Game::onTerminate(ska::TerminateProcessException& tpe) {
	SKA_LOG_MESSAGE(tpe.what());
	return 0;
}

int Game::onException(ska::GenericException& e) {
	/* Handles Generics Game exceptions */
	std::cerr << e.what() << std::endl;
	return 0;
}