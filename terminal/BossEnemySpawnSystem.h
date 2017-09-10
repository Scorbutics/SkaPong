#pragma once
#include "ECS/System.h"
#include "BossEnemyComponent.h"

class BossEnemySpawnSystem : 
	public ska::System<std::unordered_set<ska::EntityId>, ska::RequiredComponent<BossEnemyComponent>, ska::PossibleComponent<>> {
public:
	BossEnemySpawnSystem(ska::EntityManager& entityManager, ska::Rectangle& screenBox, ska::EntityId& pointOfAttraction);
	virtual ~BossEnemySpawnSystem() = default;
	
	void refresh(unsigned ellapsedTime) override;
	
private:
	ska::EntityManager& m_entityManager;
	ska::Rectangle m_screenBox;
	ska::EntityId& m_poa;
	unsigned int m_cummulatedTime;
};
