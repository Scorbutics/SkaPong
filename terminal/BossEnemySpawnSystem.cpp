#include "BossEnemySpawnSystem.h"
#include "TerminalFactory.h"

BossEnemySpawnSystem::BossEnemySpawnSystem(ska::EntityManager& entityManager, ska::Rectangle& screenBox, ska::EntityId& pointOfAttraction) :
	System(entityManager),
	m_entityManager(entityManager),
	m_screenBox(screenBox),
	m_poa(pointOfAttraction),
	m_cummulatedTime(1000) {
}

void BossEnemySpawnSystem::refresh(unsigned ellapsedTime) {
	auto& processed = getEntities();
	
	m_cummulatedTime += ellapsedTime;
	if (m_cummulatedTime >= 700) {
		m_cummulatedTime = 0;
		for (auto& entity : processed) {
			auto& bec = m_componentAccessor.get<BossEnemyComponent>(entity);

			for (auto& sp : bec.spawnPoint) {
				TerminalFactory::createBossEnemyStringEntity(m_entityManager, sp, m_poa);
			}
		}
	}
}


