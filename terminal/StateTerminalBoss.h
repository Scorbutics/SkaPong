#pragma once
#include "TerminalGameEventDispatcher.h"
#include "Core/State/StateData.h"
#include "ECS/EntityManager.h"
#include "Core/State/StateBase.h"
#include "LetterDeleterSystem.h"

namespace ska {
	class StateHolder;
	class DrawableContainer;
}

class StateTerminalBoss :
	public ska::StateBase<ska::EntityManager, TerminalGameEventDispatcher>//,
	/*public ska::SubObserver<ska::GameEvent>*/ {
public:
	StateTerminalBoss(ska::StateData<ska::EntityManager, TerminalGameEventDispatcher>& data, ska::StateHolder& sh, LetterDeleterSystem& letterDeleterSystem, ska::Rectangle& screenBox, ska::EntityId& pointOfAttraction);
	virtual void onEventUpdate(unsigned int) override;
	virtual ~StateTerminalBoss() = default;

protected:
	void beforeLoad(std::unique_ptr<State>*) override;

private:
	ska::EntityId m_poa;
	TerminalGameEventDispatcher& m_eventDispatcher;
	LetterDeleterSystem& m_letterDeleterSystem;
	ska::Rectangle& m_screenBox;
	ska::EntityManager& m_entityManager;
	ska::EntityId m_bossEntity;
};
