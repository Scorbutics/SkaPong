#include "PongFactory.h"
#include "Graphic/AnimatedTexture.h"
#include "Graphic/GraphicComponent.h"
#include "ECS/EntityManager.h"
#include "ECS/Basics/Physic/GravityAffectedComponent.h"
#include "ECS/Basics/Physic/MovementComponent.h"
#include "ECS/Basics/Physic/PositionComponent.h"
#include "ECS/Basics/Physic/CollidableComponent.h"
#include "ECS/Basics/Physic/ForceComponent.h"

const std::string& RESOURCES_FOLDER = "." FILE_SEPARATOR "Resources" FILE_SEPARATOR;

//factory
ska::EntityId PongFactory::createPongBarEntity(ska::EntityManager& m_entityManager, ska::Point<float> pos) {
	auto entity = m_entityManager.createEntity();
	ska::GraphicComponent gc;
	ska::Texture at;
	at.load(RESOURCES_FOLDER + "Sprites/0.png", 1, 1, 1);
	gc.sprites.push_back(std::move(at));
	m_entityManager.addComponent<ska::GraphicComponent>(entity, std::move(gc));
	m_entityManager.addComponent<ska::GravityAffectedComponent>(entity, ska::GravityAffectedComponent());

	ska::MovementComponent mc;
	m_entityManager.addComponent<ska::MovementComponent>(entity, std::move(mc));
	ska::PositionComponent pc;
	pc.x = pos.x;
	pc.y = pos.y;
	pc.z = 0;
	m_entityManager.addComponent<ska::PositionComponent>(entity, std::move(pc));

	m_entityManager.addComponent<ska::CollidableComponent>(entity, ska::CollidableComponent());
	ska::HitboxComponent hc;
	hc.height = at.getHeight();
	hc.width = at.getWidth();
	m_entityManager.addComponent<ska::HitboxComponent>(entity, std::move(hc));

	ska::ForceComponent fc;
	fc.weight = std::numeric_limits<float>::max();
	m_entityManager.addComponent<ska::ForceComponent>(entity, std::move(fc));

	auto& gac = m_entityManager.getComponent<ska::GravityAffectedComponent>(entity);
	gac.friction = std::numeric_limits<float>::max()*0.03F;
	return entity;
}

//factory
ska::EntityId PongFactory::createPongBallEntity(ska::EntityManager& m_entityManager, ska::Point<float> pos) {
	auto entity = m_entityManager.createEntity();
	ska::GraphicComponent gc;
	ska::Texture at;
	at.load(RESOURCES_FOLDER + "Sprites/1.png", 1, 1, 1);
	gc.sprites.push_back(at);
	m_entityManager.addComponent<ska::GraphicComponent>(entity, std::move(gc));
	ska::GravityAffectedComponent gac;
	gac.friction = 0.F;
	m_entityManager.addComponent<ska::GravityAffectedComponent>(entity, std::move(gac));
	ska::ForceComponent fc;
	fc.weight = 0.1F;
	m_entityManager.addComponent<ska::ForceComponent>(entity, std::move(fc));
	ska::MovementComponent mc;
	mc.vx = -5;
	mc.vy = -5;
	m_entityManager.addComponent<ska::MovementComponent>(entity, std::move(mc));
	ska::PositionComponent pc;
	pc.x = pos.x;
	pc.y = pos.y;
	pc.z = 0;
	m_entityManager.addComponent<ska::PositionComponent>(entity, std::move(pc));

	m_entityManager.addComponent<ska::CollidableComponent>(entity, ska::CollidableComponent());
	ska::HitboxComponent hc;
	hc.height = at.getHeight();
	hc.width = at.getWidth();
	m_entityManager.addComponent<ska::HitboxComponent>(entity, std::move(hc));
	return entity;
}

ska::EntityId PongFactory::createBoundaries(ska::EntityManager& m_entityManager, int type, ska::Rectangle screenBox) {
	auto entity = m_entityManager.createEntity();
	m_entityManager.addComponent<ska::GravityAffectedComponent>(entity, ska::GravityAffectedComponent());

	ska::MovementComponent mc;
	m_entityManager.addComponent<ska::MovementComponent>(entity, std::move(mc));
	ska::PositionComponent pc;
	pc.x = type == 2 ? -2 : (type == 3 ? screenBox.w + 1 : 0);
	pc.y = type == 0 ? -2 : (type == 1 ? screenBox.h + 1 : 0);
	pc.z = 0;
	m_entityManager.addComponent<ska::PositionComponent>(entity, std::move(pc));

	m_entityManager.addComponent<ska::CollidableComponent>(entity, ska::CollidableComponent());
	ska::HitboxComponent hc;
	hc.height = (type == 2 || type == 3) ? screenBox.h : 1;
	hc.width = (type == 0 || type == 1) ? screenBox.w : 1;
	m_entityManager.addComponent<ska::HitboxComponent>(entity, std::move(hc));

	ska::ForceComponent fc;
	fc.weight = std::numeric_limits<float>::max();
	m_entityManager.addComponent<ska::ForceComponent>(entity, std::move(fc));

	/*auto& gac = m_entityManager.getComponent<ska::GravityAffectedComponent>(entity);
	gac.friction = std::numeric_limits<float>::max()*0.03F;*/
	return entity;
}
