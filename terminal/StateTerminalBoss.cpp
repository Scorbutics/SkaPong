#include "StateTerminalBoss.h"
#include "TerminalFactory.h"
#include "BossSpawnTask.h"
#include "BossEnemySpawnSystem.h"

StateTerminalBoss::StateTerminalBoss(ska::StateData<ska::EntityManager, TerminalGameEventDispatcher>& data, ska::StateHolder& sh, LetterDeleterSystem& letterDeleterSystem, ska::Rectangle& screenBox, ska::EntityId& pointOfAttraction):
	StateBase<ska::EntityManager, ska::ExtensibleGameEventDispatcher<TerminalGUIEvent>>(data.m_entityManager, data.m_eventDispatcher, sh),
	m_eventDispatcher(data.m_eventDispatcher),
	m_entityManager(data.m_entityManager),
	m_letterDeleterSystem(letterDeleterSystem),
	m_screenBox(screenBox),
	m_poa(pointOfAttraction),
	m_bossEntity(0) {
}

void StateTerminalBoss::onEventUpdate(unsigned int ellapsedTime) {
	static long totalEllapsedTime = 0;
	if(m_entityManager.getComponent<EnemyComponent>(m_bossEntity).life > 0) {
		totalEllapsedTime += ellapsedTime;
		if(totalEllapsedTime > 5000) {
			totalEllapsedTime = 0;
			for (unsigned int index = 0; index < 20; index++) {
				TerminalFactory::createAsciiCharacterEntity(m_entityManager, ska::Point<float>(m_screenBox.w/10 + index*15, m_screenBox.h - 50));
			}
		}
	}

}

void StateTerminalBoss::beforeLoad(std::unique_ptr<State>*) {
	queueTask(std::make_unique<BossSpawnTask>(m_entityManager, m_screenBox, &m_bossEntity));	
	queueTask(std::make_unique<ska::Task>([&](ska::Task&) {
		addLogic<BossEnemySpawnSystem>(m_screenBox, m_poa);
		//TODO correct the bug that doesn't allow to instantiate a system after the entity creation
		//(here is the line that fixes it)
		m_entityManager.refreshEntity(m_bossEntity);
		return false;
	}));
}

