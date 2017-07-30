#pragma once
#include "Inputs/KeyboardInputContext.h"



	class KeyboardInputPongContext : public ska::KeyboardInputContext {
	public:
		explicit KeyboardInputPongContext(ska::RawInputListener& ril);
		virtual ~KeyboardInputPongContext();

	protected:
		virtual void buildCodeMap(std::unordered_map<int, ska::InputAction>& codeMap, std::unordered_map<int, ska::InputToggle>& toggles) override;
	};


