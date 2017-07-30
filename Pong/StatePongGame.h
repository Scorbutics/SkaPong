#pragma once
#include "ECS/EntityManager.h"
#include "Core/State/StateBase.h"
#include "Data/Events/ExtensibleGameEventDispatcher.h"
#include "Utils/SubObserver.h"
#include "Physic/System/EntityCollisionResponse.h"
#include "World.h"

class StatePongGame :
	public ska::StateBase<ska::EntityManager, ska::ExtensibleGameEventDispatcher<>> {
public:
	StatePongGame(StateData& data, ska::StateHolder& sh, unsigned int windowWidth, unsigned int windowHeight);
	
	virtual ~StatePongGame() = default;

private:
	ska::EntityId createPhysicAABBEntity(ska::Point<int> pos) const;

	ska::CameraSystem* m_cameraSystem;
	World m_world;
	ska::ExtensibleGameEventDispatcher<>& m_eventDispatcher;
	ska::EntityManager& m_entityManager;
	ska::EntityCollisionResponse m_entityCollision;
};
