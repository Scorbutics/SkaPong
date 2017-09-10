#pragma once
#include "ECS/EntityManager.h"
#include "Core/State/StateBase.h"
#include "Data/Events/ExtensibleGameEventDispatcher.h"
#include "GUI.h"
#include "Utils/SubObserver.h"
#include "TerminalGameEventDispatcher.h"

namespace ska {
	class Image;
}

class StateScreenTitle : 
	public ska::StateBase<ska::EntityManager, TerminalGameEventDispatcher>,
	public ska::SubObserver<ska::GameEvent> {
public:
	StateScreenTitle(StateData& data, ska::StateHolder& sh, GUI& gui);
	virtual void onGraphicUpdate(unsigned int, ska::DrawableContainer&) override;
	virtual void onEventUpdate(unsigned int) override;
	virtual ~StateScreenTitle() = default;

private:
	bool onGameEvent(ska::GameEvent& ge) const;

protected:
	bool afterUnload() override;

private:
	TerminalGameEventDispatcher& m_eventDispatcher;
	GUI& m_gui;
	ska::DynamicWindowIG<>* m_pressStartWindow;
	ska::Image* m_backgroundImage;
};
