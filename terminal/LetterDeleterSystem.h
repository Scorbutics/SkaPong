#pragma once
#include "ECS/System.h"
#include "ECS/Basics/Physic/PositionComponent.h"
#include "CharacterComponent.h"
#include "ECS/Basics/Physic/ForceComponent.h"
#include "ECS/Basics/Input/InputComponent.h"
#include "Utils/SubObserver.h"
#include "Data/Events/InputKeyEvent.h"
#include "Data/Events/GameEventDispatcher.h"
#include "Graphic/System/DeleterSystem.h"
#include "EnemyComponent.h"
#include "TerminalGameEventDispatcher.h"

namespace ska {
	class InputSystem;
}

class LetterDeleterSystem : 
	public ska::System<std::unordered_set<ska::EntityId>, ska::RequiredComponent<>, ska::PossibleComponent<CharacterComponent, EnemyComponent>>,
	public ska::SubObserver<ska::CollisionEvent>,
	public ska::SubObserver<ska::ECSEvent> {

public:
	LetterDeleterSystem(ska::EntityManager& entityManager, TerminalGameEventDispatcher& ged);
	LetterDeleterSystem& operator=(const ska::InputSystem&) = delete;

	unsigned int getTotalLetter() const;
	unsigned getTotalEnemy() const;

	virtual ~LetterDeleterSystem() = default;
	void createLetter(ska::Rectangle& screenBox);
	void createEnemy(ska::Rectangle& screenBox);

private:
	ska::EntityManager& m_entityManager;
	unsigned int m_totalLetter;
	unsigned int m_totalEnemy;
	bool onCollisionEvent(ska::CollisionEvent & ce);
	bool onEcsEvent(ska::ECSEvent & ecsEvent);
	TerminalGameEventDispatcher& m_eventDispatcher;

protected:
	virtual void refresh(unsigned int ellapsedTime) override;

};
