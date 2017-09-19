#include "Game.h"
#include "Inputs/KeyboardInputGUIContext.h"
#include "StateScreenTitle.h"
#include "Draw/SDLFont.h"
#include "KeyboardInputPongContext.h"

std::unique_ptr<ska::GameApp> ska::GameApp::get() {
	auto wgc = std::make_unique<Game>();
	wgc->init();
	return wgc;
}

void Game::init() {
	/* Configure inputs types */
	addInputContext<KeyboardInputPongContext>(ska::EnumContextManager::CONTEXT_MAP);
	addInputContext<ska::KeyboardInputGUIContext>(ska::EnumContextManager::CONTEXT_GUI);

	ska::GUI::MENU_DEFAULT_THEME_PATH = "." FILE_SEPARATOR "Resources" FILE_SEPARATOR "Menu" FILE_SEPARATOR "start_screen_theme" FILE_SEPARATOR;
	ska::SDLFont::DEFAULT_FONT_FILE = "." FILE_SEPARATOR "Resources" FILE_SEPARATOR "Fonts" FILE_SEPARATOR "FiraSans-Medium.ttf";
	navigateToState<StateScreenTitle>();
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