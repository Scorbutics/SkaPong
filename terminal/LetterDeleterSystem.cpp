#include "LetterDeleterSystem.h"
#include "ECS/Basics/Physic/CollisionComponent.h"
#include "TerminalFactory.h"
#include "EnemyComponent.h"
#include "ECS/Basics/Graphic/DeleterComponent.h"
#include "ECS/Basics/Physic/MovementComponent.h"
#include "TerminalGUIEvent.h"
#include "BossEnemyComponent.h"

LetterDeleterSystem::LetterDeleterSystem(ska::EntityManager& entityManager, TerminalGameEventDispatcher& ged) :
	System(entityManager),
	ska::SubObserver<ska::CollisionEvent>(std::bind(&LetterDeleterSystem::onCollisionEvent, this, std::placeholders::_1), ged), 
	ska::SubObserver<ska::ECSEvent>(std::bind(&LetterDeleterSystem::onEcsEvent, this, std::placeholders::_1), ged),
	m_entityManager(entityManager),
	m_eventDispatcher(ged),
	m_totalLetter(0),
	m_totalEnemy(0){}

unsigned LetterDeleterSystem::getTotalLetter() const {
	return m_totalLetter;
}

unsigned LetterDeleterSystem::getTotalEnemy() const {
	return m_totalEnemy;
}

void LetterDeleterSystem::createLetter(ska::Rectangle& screenBox) {
	TerminalFactory::createAsciiCharacterEntity(m_entityManager, ska::Point<int>(ska::NumberUtils::random(0, screenBox.w), 0));
	m_totalLetter++;
}

void LetterDeleterSystem::createEnemy(ska::Rectangle& screenBox) {
	auto enemyEntity = TerminalFactory::createEnemyStringEntity(m_entityManager, screenBox);
	auto& mc = m_entityManager.getComponent<ska::MovementComponent>(enemyEntity);
	mc.vy += 5.F;
	m_totalEnemy++;
}

bool LetterDeleterSystem::onCollisionEvent(ska::CollisionEvent& ce) {
	if(ce.collisionComponent == nullptr) {
		return false;
	}

	auto& col = *ce.collisionComponent;
	if(m_entityManager.hasComponent<CharacterComponent>(col.origin) ||
		m_entityManager.hasComponent<CharacterComponent>(col.target)) {
		auto letter = m_entityManager.hasComponent<CharacterComponent>(col.origin) ? col.origin : col.target;
		auto& cc = m_entityManager.getComponent<CharacterComponent>(letter);
		if(cc.life <= 0) {
			m_entityManager.removeEntity(letter);			
		}
	}

	if (m_entityManager.hasComponent<EnemyComponent>(col.origin) ||
		m_entityManager.hasComponent<EnemyComponent>(col.target)) {
		auto letter = m_entityManager.hasComponent<EnemyComponent>(col.origin) ? col.origin : col.target;
		auto& cc = m_entityManager.getComponent<EnemyComponent>(letter);
		if (cc.life <= 0) {
			m_entityManager.removeEntity(letter);
			TerminalGUIEvent tge(UPDATE_SCORE);
			tge.score = m_entityManager.hasComponent<BossEnemyComponent>(letter) ? 50 : 1;
			m_eventDispatcher.ska::Observable<TerminalGUIEvent>::notifyObservers(tge);
		}
	}
	return true;
}

bool LetterDeleterSystem::onEcsEvent(ska::ECSEvent& ecsEvent) {
	if(ecsEvent.ecsEventType != ska::ENTITIES_REMOVED) {
		return false;
	}

	auto& processed = ecsEvent.entities;
	for (auto entityId : processed) {
		if (m_entityManager.hasComponent<EnemyComponent>(entityId)) {
			m_totalEnemy--;	
		} else if (m_entityManager.hasComponent<CharacterComponent>(entityId)) {			
			m_totalLetter--;
		}
	}
	return true;
}

void LetterDeleterSystem::refresh(unsigned int) {
}
