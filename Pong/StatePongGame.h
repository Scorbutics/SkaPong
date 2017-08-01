#pragma once
#include "ECS/EntityManager.h"
#include "Core/State/StateBase.h"
#include "Data/Events/ExtensibleGameEventDispatcher.h"
#include "Physic/System/EntityCollisionResponse.h"
#include "World.h"
#include "Physic/System/WorldCollisionResponse.h"
#include "PongBallGoalCollisionResponse.h"
#include "AI.h"

class StatePongGame :
	public ska::StateBase<ska::EntityManager, ska::ExtensibleGameEventDispatcher<>> {
public:
	StatePongGame(StateData& data, ska::StateHolder& sh, unsigned int windowWidth, unsigned int windowHeight);
	virtual void onEventUpdate(unsigned int ellapsedTime) override;
	virtual ~StatePongGame() = default;

private:
	ska::CameraSystem* m_cameraSystem;
	World m_world;
	ska::ExtensibleGameEventDispatcher<>& m_eventDispatcher;
	ska::EntityManager& m_entityManager;

	ska::EntityCollisionResponse m_entityCollision;
	ska::EntityId m_ball;
	std::unique_ptr<PongBallGoalCollisionResponse> m_scoreMaker;
	AI m_ai;
	ska::EntityId m_enemyBar;
};
