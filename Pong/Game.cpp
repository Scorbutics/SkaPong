#include "Game.h"
#include "Inputs/KeyboardInputGUIContext.h"
#include "StateScreenTitle.h"
#include "Draw/SDLFont.h"
#include "KeyboardInputPongContext.h"

ska::GameApp& ska::GameApp::get() {
	static Game wgc;
	wgc.init();
	return wgc;
}

void Game::init() {
	/* Configure inputs types */
	addInputContext<KeyboardInputPongContext>(ska::EnumContextManager::CONTEXT_MAP);
	addInputContext<ska::KeyboardInputGUIContext>(ska::EnumContextManager::CONTEXT_GUI);

	ska::GUI::MENU_DEFAULT_THEME_PATH = "." FILE_SEPARATOR "Resources" FILE_SEPARATOR "Menu" FILE_SEPARATOR "default_theme" FILE_SEPARATOR;
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