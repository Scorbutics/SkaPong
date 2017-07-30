#pragma once
#include "Utils/SubObserver.h"
#include "Data/Events/CollisionEvent.h"
#include "ECS/EntityManager.h"
#include "Data/Events/ExtensibleGameEventDispatcher.h"

namespace ska {
	class CameraSystem;
}

class PongBallGoalCollisionResponse :
	public ska::SubObserver<ska::CollisionEvent> {
public:
	PongBallGoalCollisionResponse(ska::EntityManager & entityManager, ska::ExtensibleGameEventDispatcher<>& eventDispatcher, ska::CameraSystem& cameraSystem, ska::EntityId ball, ska::EntityId barEnemy, ska::EntityId barAlly);
	
	virtual ~PongBallGoalCollisionResponse() = default;

private:
	bool isBarCollision(ska::CollisionEvent& ce) const;
	bool onCollisionEvent(ska::CollisionEvent& ce) const;
	void resetBallPosition() const;

	ska::EntityId m_ball;
	ska::EntityManager& m_entityManager;
	ska::CameraSystem& m_cameraSystem;
	ska::EntityId m_barEnemy;
	ska::EntityId m_barAlly;

};
