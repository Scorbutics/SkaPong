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
	
	//Side Collisions => win or lose
	if (ce.wcollisionComponent != nullptr) {
		auto& wcol = *ce.wcollisionComponent;
		if ((wcol.xaxis || wcol.yaxis) && ce.entity == m_ball) {
			if (!wcol.blockColPosX.empty()) {
				auto& block = wcol.blockColPosX[0];
				if (block.x <= 0) {
					resetBallPosition();
				} else if (block.x + 30 >= m_cameraSystem.getDisplay()->w) {					
					resetBallPosition();
				}
				return true;
			}
		}
		return true;
	}

	//Collisions with bars
	if(ce.collisionComponent != nullptr && isBarCollision(ce)) {
		//when collided with an entity, put a lateral acceleration on the ball depending on the velocity of the entity
		auto& col = *ce.collisionComponent;
		
		auto entity = col.origin == m_ball ? col.target : col.origin;
		
		auto& mc = m_entityManager.getComponent<ska::MovementComponent>(entity);
		auto& fcBall = m_entityManager.getComponent<ska::ForceComponent>(m_ball);
		auto& pcBall = m_entityManager.getComponent<ska::PositionComponent>(m_ball);
		auto& pcBar = m_entityManager.getComponent<ska::PositionComponent>(entity);
		fcBall.y += mc.vy * 0.05F;
		fcBall.x += mc.vy * 0.05F * (pcBar.x > pcBall.x ? -1 : 1);
		return true;
	}

	return false;
}
