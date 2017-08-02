#include "PongBallGoalCollisionResponse.h"
#include "Data/Events/ExtensibleGameEventDispatcher.h"
#include "ECS/Basics/Physic/PositionComponent.h"
#include "ECS/Basics/Physic/MovementComponent.h"
#include "Graphic/System/CameraSystem.h"
#include "ECS/Basics/Physic/WorldCollisionComponent.h"
#include "ECS/Basics/Physic/CollisionComponent.h"
#include "ECS/Basics/Physic/ForceComponent.h"

PongBallGoalCollisionResponse::PongBallGoalCollisionResponse(ska::EntityManager & entityManager, ska::ExtensibleGameEventDispatcher<>& eventDispatcher, ska::CameraSystem& cameraSystem, ska::EntityId ball, ska::EntityId barEnemy, ska::EntityId barAlly) :
	SubObserver<ska::CollisionEvent>(std::bind(&PongBallGoalCollisionResponse::onCollisionEvent, this, std::placeholders::_1), eventDispatcher),
	m_ball(ball),
	m_entityManager(entityManager),
	m_cameraSystem(cameraSystem),
	m_barEnemy(barEnemy),
	m_barAlly(barAlly) {}

void PongBallGoalCollisionResponse::resetBallPosition() const{
	auto& pc = m_entityManager.getComponent<ska::PositionComponent>(m_ball);
	pc.x = m_cameraSystem.getDisplay()->w / 2;
	pc.y = m_cameraSystem.getDisplay()->h / 2;

	auto& mc = m_entityManager.getComponent<ska::MovementComponent>(m_ball);
	auto velocityPoint = ska::Point<int>::cartesian(7, ska::NumberUtils::random(-M_PI / 2 + 1, M_PI / 2 - 1) + (ska::NumberUtils::random(0, 1) * M_PI ));
	mc.vx = velocityPoint.x;
	mc.vy = velocityPoint.y;
}

bool PongBallGoalCollisionResponse::isBarCollision(ska::CollisionEvent& ce) const {
	auto& col = *ce.collisionComponent;
	return (col.target == m_barEnemy && col.origin == m_ball || col.target == m_barAlly && col.origin == m_ball) || (col.origin == m_barEnemy && col.target == m_ball || col.origin == m_barAlly && col.target == m_ball) ;
}

bool PongBallGoalCollisionResponse::onCollisionEvent(ska::CollisionEvent & ce) const{
	if(ce.collisionComponent != nullptr) {
        auto& col = *ce.collisionComponent;

        auto entity = col.origin == m_ball ? col.target : col.origin;
        auto& pcBall = m_entityManager.getComponent<ska::PositionComponent>(m_ball);

        if(isBarCollision(ce)) {
            //when collided with an entity, put a lateral acceleration on the ball depending on the velocity of the entity
            auto& mc = m_entityManager.getComponent<ska::MovementComponent>(entity);
            auto& fcBall = m_entityManager.getComponent<ska::ForceComponent>(m_ball);
            auto& pcEntity = m_entityManager.getComponent<ska::PositionComponent>(entity);
            fcBall.y += mc.vy * 0.05F;
            return true;
        }
        auto& hitboxEntity = m_entityManager.getComponent<ska::HitboxComponent>(entity);

        //when collided with left and right sides boundaries
        if(hitboxEntity.width <= 1 || pcBall.x < 30 || pcBall.x >= m_cameraSystem.getDisplay()->w - 30) {
            resetBallPosition();
            return true;
        }
    }

	return false;
}
