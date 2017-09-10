#include "EnemyAllyCollisionResponse.h"
#include "Data/Events/ExtensibleGameEventDispatcher.h"
#include "ECS/Basics/Physic/PositionComponent.h"
#include "ECS/Basics/Physic/MovementComponent.h"
#include "Graphic/System/CameraSystem.h"
#include "ECS/Basics/Physic/WorldCollisionComponent.h"
#include "ECS/Basics/Physic/CollisionComponent.h"
#include "CharacterComponent.h"
#include "EnemyComponent.h"
#include "ECS/Basics/Physic/ForceComponent.h"
#include "ECS/Basics/Input/InputComponent.h"

EnemyAllyCollisionResponse::EnemyAllyCollisionResponse(ska::EntityManager & entityManager, TerminalGameEventDispatcher& eventDispatcher, ska::CameraSystem& cameraSystem) :
	SubObserver<ska::CollisionEvent>(std::bind(&EnemyAllyCollisionResponse::onCollisionEvent, this, std::placeholders::_1), eventDispatcher),
	m_entityManager(entityManager),
	m_cameraSystem(cameraSystem),
	m_eventDispatcher(eventDispatcher) {
	
}

bool EnemyAllyCollisionResponse::isLetterEnemyCollision(ska::CollisionEvent& ce) const {
	auto& col = *ce.collisionComponent;
	return (m_entityManager.hasComponent<CharacterComponent>(col.target) && m_entityManager.hasComponent<EnemyComponent>(col.origin) 
		|| m_entityManager.hasComponent<CharacterComponent>(col.origin) && m_entityManager.hasComponent<EnemyComponent>(col.target));
}

bool EnemyAllyCollisionResponse::onCollisionEvent(ska::CollisionEvent & ce) const{
	
	//Side Collisions => win or lose
	/*if (ce.wcollisionComponent != nullptr) {
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
	}*/
	
	//Collisions letters and enemy
	if (ce.collisionComponent != nullptr) {
		auto& col = *ce.collisionComponent;
		if (isLetterEnemyCollision(ce)) {
			auto enemy = m_entityManager.hasComponent<CharacterComponent>(col.origin) ? col.target : col.origin;
			auto letter = m_entityManager.hasComponent<EnemyComponent>(col.origin) ? col.target : col.origin;

			auto& ec = m_entityManager.getComponent<EnemyComponent>(enemy);
			ec.life -= 10;

			auto& cc = m_entityManager.getComponent<CharacterComponent>(letter);
			cc.life--;

			return true;
		}

		if(m_entityManager.hasComponent<EnemyComponent>(col.origin) || 
			m_entityManager.hasComponent<EnemyComponent>(col.target)) {
			auto notEnemy = m_entityManager.hasComponent<EnemyComponent>(col.origin) ? col.target : col.origin;			
			auto& hcOther = m_entityManager.getComponent<ska::HitboxComponent>(notEnemy);
			
			//Way of checking if it's the screen bottom/top line border
			if(hcOther.width == m_cameraSystem.getDisplay()->w) {
				auto& enemy = m_entityManager.hasComponent<EnemyComponent>(col.origin) ? col.origin : col.target;
				m_entityManager.removeEntity(enemy);
			}

			//Way of checking if it's the screen right/left line border
			if (hcOther.height == m_cameraSystem.getDisplay()->h) {
				auto& enemy = m_entityManager.hasComponent<EnemyComponent>(col.origin) ? col.origin : col.target;
				m_entityManager.removeEntity(enemy);
			}

			//Punish the player to have hit the enemy !
			if(m_entityManager.hasComponent<ska::InputComponent>(notEnemy)) {
				TerminalGUIEvent tge(UPDATE_TIME);
				tge.time = 10000;
				m_eventDispatcher.ska::Observable<TerminalGUIEvent>::notifyObservers(tge);
				auto& enemy = m_entityManager.hasComponent<EnemyComponent>(col.origin) ? col.origin : col.target;
				m_entityManager.removeEntity(enemy);
			}
		}
	}
	
	return false;
}
