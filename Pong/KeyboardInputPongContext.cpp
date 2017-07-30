#include <SDL.h>
#include "Inputs/RawInputListener.h"
#include "KeyboardInputPongContext.h"


KeyboardInputPongContext::KeyboardInputPongContext(ska::RawInputListener& ril) : KeyboardInputContext(ril) {
}

void KeyboardInputPongContext::buildCodeMap(std::unordered_map<int, ska::InputAction>& codeMap, std::unordered_map<int, ska::InputToggle>& toggles) {
	
	codeMap[SDL_SCANCODE_ESCAPE] = ska::Quit;

	toggles[SDL_SCANCODE_W] = ska::MoveUp;
	toggles[SDL_SCANCODE_S] = ska::MoveDown;

	/* Mouse click */
	/* Left */
	toggles[SDL_NUM_SCANCODES + 0] = ska::MoveTo;
}

KeyboardInputPongContext::~KeyboardInputPongContext() {
}
