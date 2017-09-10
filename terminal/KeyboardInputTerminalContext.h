#pragma once
#include "Inputs/KeyboardInputContext.h"



	class KeyboardInputTerminalContext : public ska::KeyboardInputContext {
	public:
		explicit KeyboardInputTerminalContext(ska::RawInputListener& ril);
		virtual ~KeyboardInputTerminalContext();

	protected:
		virtual void buildCodeMap(std::unordered_map<int, ska::InputAction>& codeMap, std::unordered_map<int, ska::InputToggle>& toggles) override;
	};


