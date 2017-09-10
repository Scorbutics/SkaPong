#include <SDL.h>
#include "Inputs/RawInputListener.h"
#include "KeyboardInputTerminalContext.h"


KeyboardInputTerminalContext::KeyboardInputTerminalContext(ska::RawInputListener& ril) : KeyboardInputContext(ril) {
}

void KeyboardInputTerminalContext::buildCodeMap(std::unordered_map<int, ska::InputAction>& codeMap, std::unordered_map<int, ska::InputToggle>& toggles) {
	toggles[SDL_SCANCODE_W] = ska::MoveUp;
	toggles[SDL_SCANCODE_A] = ska::MoveLeft;
	toggles[SDL_SCANCODE_D] = ska::MoveRight;
	toggles[SDL_SCANCODE_S] = ska::MoveDown;

	codeMap[SDL_SCANCODE_SPACE] = ska::Jump;
	codeMap[SDL_SCANCODE_LCTRL] = ska::DoAction;
}

KeyboardInputTerminalContext::~KeyboardInputTerminalContext() {
}
