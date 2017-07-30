#include "StatePongGame.h"
#include "Graphic/System/GraphicSystem.h"
#include "GUI/Components/Concrete/Button.h"
#include "ECS/Basics/Physic/GravityAffectedComponent.h"
#include "ECS/Basics/Physic/ForceComponent.h"
#include "ECS/Basics/Physic/MovementComponent.h"
#include "ECS/Basics/Physic/CollidableComponent.h"
#include "Graphic/System/CameraFixedSystem.h"
#include "Physic/System/MovementSystem.h"
#include "Physic/System/CollisionSystem.h"
#include "Physic/System/GravitySystem.h"
#include "Inputs/System/InputSystem.h"

const std::string& RESOURCES_FOLDER = "." FILE_SEPARATOR "Resources" FILE_SEPARATOR;

StatePongGame::StatePongGame(StateData & data, ska::StateHolder & sh, unsigned int windowWidth, unsigned int windowHeight):
	StateBase(data.m_entityManager, data.m_eventDispatcher, sh),
	m_cameraSystem(nullptr),
	m_eventDispatcher(data.m_eventDispatcher),
	m_entityManager(data.m_entityManager),
	m_entityCollision(data.m_eventDispatcher, data.m_entityManager) {

	m_cameraSystem = addLogic<ska::CameraFixedSystem>(windowWidth, windowHeight, ska::Point<int>());
	addGraphic<ska::GraphicSystem>(m_eventDispatcher, m_cameraSystem);

	addLogic<ska::MovementSystem>();
	addLogic<ska::CollisionSystem>(m_world, m_eventDispatcher);
	addLogic<ska::GravitySystem>();
	addLogic<ska::InputSystem>(m_eventDispatcher);

	auto blockA = createPhysicAABBEntity(ska::Point<int>(30, windowHeight/2));
	auto blockB = createPhysicAABBEntity(ska::Point<int>(windowWidth - 30, windowHeight / 2));

	ska::InputComponent ic;
	ic.movePower = std::numeric_limits<float>::max()*0.5F;
	m_entityManager.addComponent<ska::InputComponent>(blockA, ic);

	auto& fc = m_entityManager.getComponent<ska::ForceComponent>(blockA);
	fc.weight = std::numeric_limits<float>::max();
	auto& gac = m_entityManager.getComponent<ska::GravityAffectedComponent>(blockA);
	gac.friction = std::numeric_limits<float>::max()*0.03F;
}

//factory
ska::EntityId StatePongGame::createPhysicAABBEntity(ska::Point<int> pos) const {
	auto entity = m_entityManager.createEntity();
	ska::GraphicComponent gc;
	ska::AnimatedTexture at;
	at.load(RESOURCES_FOLDER + "Sprites/0.png", 1, 1, 1);
	gc.sprite.push_back(at);
	m_entityManager.addComponent<ska::GraphicComponent>(entity, gc);
	m_entityManager.addComponent<ska::GravityAffectedComponent>(entity, ska::GravityAffectedComponent());
	ska::ForceComponent fc;
	m_entityManager.addComponent<ska::ForceComponent>(entity, fc);
	ska::MovementComponent mc;
	m_entityManager.addComponent<ska::MovementComponent>(entity, mc);
	ska::PositionComponent pc;
	pc.x = pos.x;
	pc.y = pos.y;
	pc.z = 0;
	m_entityManager.addComponent<ska::PositionComponent>(entity, pc);

	m_entityManager.addComponent<ska::CollidableComponent>(entity, ska::CollidableComponent());
	ska::HitboxComponent hc;
	hc.height = at.getHeight();
	hc.width = at.getWidth();
	m_entityManager.addComponent<ska::HitboxComponent>(entity, hc);
	return entity;
}

