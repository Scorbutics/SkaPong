#include <SDL.h>
#include "Inputs/RawInputListener.h"
#include "KeyboardInputPongContext.h"


KeyboardInputPongContext::KeyboardInputPongContext(ska::RawInputListener& ril) : KeyboardInputContext(ril) {
}

void KeyboardInputPongContext::buildCodeMap(std::unordered_map<int, ska::InputAction>& codeMap, std::unordered_map<int, ska::InputToggle>& toggles) {
	toggles[SDL_SCANCODE_W] = ska::MoveUp;
	toggles[SDL_SCANCODE_S] = ska::MoveDown;
}

KeyboardInputPongContext::~KeyboardInputPongContext() {
}
