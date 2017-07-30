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
	ska::AnimatedTexture at;
	at.load(RESOURCES_FOLDER + "Sprites/0.png", 1, 1, 1);
	gc.sprite.push_back(at);
	m_entityManager.addComponent<ska::GraphicComponent>(entity, gc);
	m_entityManager.addComponent<ska::GravityAffectedComponent>(entity, ska::GravityAffectedComponent());

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

	ska::ForceComponent fc;
	fc.weight = std::numeric_limits<float>::max();
	m_entityManager.addComponent<ska::ForceComponent>(entity, fc);

	auto& gac = m_entityManager.getComponent<ska::GravityAffectedComponent>(entity);
	gac.friction = std::numeric_limits<float>::max()*0.03F;
	return entity;
}

//factory
ska::EntityId PongFactory::createPongBallEntity(ska::EntityManager& m_entityManager, ska::Point<float> pos) {
	auto entity = m_entityManager.createEntity();
	ska::GraphicComponent gc;
	ska::AnimatedTexture at;
	at.load(RESOURCES_FOLDER + "Sprites/1.png", 1, 1, 1);
	gc.sprite.push_back(at);
	m_entityManager.addComponent<ska::GraphicComponent>(entity, gc);
	ska::GravityAffectedComponent gac;
	gac.friction = 0.F;
	m_entityManager.addComponent<ska::GravityAffectedComponent>(entity, gac);
	ska::ForceComponent fc;
	fc.weight = 0.1F;
	m_entityManager.addComponent<ska::ForceComponent>(entity, fc);
	ska::MovementComponent mc;
	mc.vx = -5;
	mc.vy = -5;
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

ska::EntityId PongFactory::createTopAndBottomBoundaries(ska::EntityManager& m_entityManager, bool top, ska::Rectangle screenBox) {
	auto entity = m_entityManager.createEntity();
	m_entityManager.addComponent<ska::GravityAffectedComponent>(entity, ska::GravityAffectedComponent());

	ska::MovementComponent mc;
	m_entityManager.addComponent<ska::MovementComponent>(entity, mc);
	ska::PositionComponent pc;
	pc.x = 0;
	pc.y = top ? -1 : screenBox.h;
	pc.z = 0;
	m_entityManager.addComponent<ska::PositionComponent>(entity, pc);

	m_entityManager.addComponent<ska::CollidableComponent>(entity, ska::CollidableComponent());
	ska::HitboxComponent hc;
	hc.height = 1;
	hc.width = screenBox.w;
	m_entityManager.addComponent<ska::HitboxComponent>(entity, hc);

	ska::ForceComponent fc;
	fc.weight = std::numeric_limits<float>::max();
	m_entityManager.addComponent<ska::ForceComponent>(entity, fc);

	/*auto& gac = m_entityManager.getComponent<ska::GravityAffectedComponent>(entity);
	gac.friction = std::numeric_limits<float>::max()*0.03F;*/
	return entity;
}
