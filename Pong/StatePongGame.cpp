#include "StatePongGame.h"
#include "Graphic/System/GraphicSystem.h"
#include "Graphic/System/CameraFixedSystem.h"
#include "Physic/System/MovementSystem.h"
#include "Physic/System/CollisionSystem.h"
#include "Physic/System/GravitySystem.h"
#include "Inputs/System/InputSystem.h"
#include "PongFactory.h"
#include "PongBallGoalCollisionResponse.h"

StatePongGame::StatePongGame(StateData& data, ska::StateHolder & sh, unsigned int windowWidth, unsigned int windowHeight):
	StateBase(data.m_entityManager, data.m_eventDispatcher, sh),
	m_cameraSystem(nullptr),
	m_eventDispatcher(data.m_eventDispatcher),
	m_entityManager(data.m_entityManager),
	m_entityCollision(data.m_eventDispatcher, data.m_entityManager),
	m_ai(data.m_entityManager) {
	m_cameraSystem = addLogic<ska::CameraFixedSystem>(windowWidth, windowHeight, ska::Point<int>());
	addGraphic<ska::GraphicSystem>(m_eventDispatcher, m_cameraSystem);

	addLogic<ska::MovementSystem>();
	addLogic<ska::CollisionSystem>(m_eventDispatcher);
	addLogic<ska::GravitySystem>();
	addLogic<ska::InputSystem>(m_eventDispatcher);

	ska::Rectangle screenBox{0, 0, static_cast<int>(windowWidth), static_cast<int>(windowHeight)};
	PongFactory::createBoundaries(m_entityManager, 0, screenBox);
	PongFactory::createBoundaries(m_entityManager, 1, screenBox);
    PongFactory::createBoundaries(m_entityManager, 2, screenBox);
	PongFactory::createBoundaries(m_entityManager, 3, screenBox);

	auto blockA = PongFactory::createPongBarEntity(m_entityManager, ska::Point<int>(10, windowHeight / 2));
	m_enemyBar = PongFactory::createPongBarEntity(m_entityManager, ska::Point<int>(windowWidth - 30, windowHeight / 2));
	m_ball = PongFactory::createPongBallEntity(m_entityManager, ska::Point<int>(windowWidth / 2, windowHeight / 2));

	ska::InputComponent ic;
	ic.movePower = std::numeric_limits<float>::max() * 0.5F;
	m_entityManager.addComponent<ska::InputComponent>(blockA, std::move(ic));

	m_scoreMaker = std::make_unique<PongBallGoalCollisionResponse>(m_entityManager, m_eventDispatcher, *m_cameraSystem, m_ball, m_enemyBar, blockA);
}

void StatePongGame::onEventUpdate(unsigned int) {
	m_ai.update(m_enemyBar, m_ball);
}


