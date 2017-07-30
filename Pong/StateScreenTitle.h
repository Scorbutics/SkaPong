#pragma once
#include "ECS/EntityManager.h"
#include "Core/State/StateBase.h"
#include "Data/Events/ExtensibleGameEventDispatcher.h"
#include "GUI.h"
#include "Utils/SubObserver.h"


namespace ska {
	class Image;
}

class StateScreenTitle : 
	public ska::StateBase<ska::EntityManager, ska::ExtensibleGameEventDispatcher<>>,
	public ska::SubObserver<ska::GameEvent> {
public:
	StateScreenTitle(StateData& data, ska::StateHolder& sh);
	virtual void onGraphicUpdate(unsigned int, ska::DrawableContainer&) override;
	virtual void onEventUpdate(unsigned int) override;
	virtual ~StateScreenTitle() = default;

private:
	bool onGameEvent(ska::GameEvent& ge) const;

	GUI m_gui;
	ska::DynamicWindowIG<>* m_pressStartWindow;
	ska::Image* m_backgroundImage;
};
