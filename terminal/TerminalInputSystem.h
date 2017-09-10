#pragma once
#include <unordered_set>
#include "Physic/System/MovementSystem.h"
#include "ECS/Basics/Input/InputComponent.h"
#include "Utils/SubObserver.h"
#include "Data/Events/GameEventDispatcher.h"
#include "CharacterComponent.h"

namespace ska {
	class InputSystem;
	struct InputKeyEvent;
}

class TerminalInputSystem : 
	public ska::System<std::unordered_set<ska::EntityId>, ska::RequiredComponent<ska::PositionComponent, CharacterComponent, ska::ForceComponent>, ska::PossibleComponent<ska::InputComponent>>,
	public ska::SubObserver<ska::InputKeyEvent> {
private:
		 
	public:
		TerminalInputSystem(ska::EntityManager& entityManager, ska::GameEventDispatcher& ged, ska::EntityId& pointOfAttraction);
		TerminalInputSystem& operator=(const ska::InputSystem&) = delete;
		virtual ~TerminalInputSystem() = default;

	private:
		bool onKeyInputEvent(ska::InputKeyEvent & ike);
		ska::GameEventDispatcher& m_eventDispatcher;
		ska::EntityId m_poa;

protected:
		virtual void refresh(unsigned int ellapsedTime) override;

};
