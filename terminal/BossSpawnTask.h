#pragma once
#include "Task/Task.h"
#include "ECS/EntityManager.h"
#include "TerminalGameEventDispatcher.h"
#include "TerminalFactory.h"

class BossSpawnTask : 
	public ska::Task {
public:
	BossSpawnTask(ska::EntityManager& em, ska::Rectangle& screenBox, ska::EntityId* bossEntity) : 
	Task([&] (Task& t) {
		if (!m_bossSpawned) {
			m_boss = TerminalFactory::createEnemyBossEntity(em, screenBox);
			*m_bossEntity = m_boss;
			m_bossSpawned = true;
		}

		auto& pc = em.getComponent<ska::PositionComponent>(m_boss);
		pc.y += 0.3F;

		return pc.y < 100;
	}), m_bossSpawned(false),
		m_boss(0),
		m_bossEntity(bossEntity){}

	virtual ~BossSpawnTask() = default;
private:
	bool m_bossSpawned;
	ska::EntityId m_boss;
	ska::EntityId *m_bossEntity;
};
