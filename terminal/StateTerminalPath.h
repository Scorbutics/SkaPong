#pragma once
#include "Core/State/StateData.h"
#include "TerminalGameEventDispatcher.h"
#include "ECS/EntityManager.h"
#include "Core/State/StateBase.h"
#include "LetterDeleterSystem.h"

class GUI;

namespace ska {
	class StateHolder;
	class DrawableContainer;
}

class StateTerminalPath :
	public ska::StateBase<ska::EntityManager, TerminalGameEventDispatcher> {
public:
	StateTerminalPath(ska::StateData<ska::EntityManager, TerminalGameEventDispatcher>& data, ska::StateHolder& sh, GUI& gui, LetterDeleterSystem& letterDeleterSystem, ska::Rectangle& screenBox);
	virtual void onEventUpdate(unsigned int ellapsedTime) override;
	virtual ~StateTerminalPath() = default;

protected:
	void onGraphicUpdate(unsigned, ska::DrawableContainer&) override;
	LetterDeleterSystem& m_letterDeleterSystem;
	SDL_Rect& m_screenBox;
};
