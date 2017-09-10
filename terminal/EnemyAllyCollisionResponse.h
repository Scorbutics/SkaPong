#pragma once
#include "Utils/SubObserver.h"
#include "Data/Events/CollisionEvent.h"
#include "ECS/EntityManager.h"
#include "Data/Events/ExtensibleGameEventDispatcher.h"
#include "TerminalGameEventDispatcher.h"

namespace ska {
	class CameraSystem;
}

class EnemyAllyCollisionResponse :
	public ska::SubObserver<ska::CollisionEvent> {
public:
	EnemyAllyCollisionResponse(ska::EntityManager & entityManager, TerminalGameEventDispatcher& eventDispatcher, ska::CameraSystem& cameraSysteml);
	virtual ~EnemyAllyCollisionResponse() = default;

private:
	bool isLetterEnemyCollision(ska::CollisionEvent& ce) const;
	bool onCollisionEvent(ska::CollisionEvent& ce) const;

	ska::EntityManager& m_entityManager;
	ska::CameraSystem& m_cameraSystem;
	TerminalGameEventDispatcher& m_eventDispatcher;

};
