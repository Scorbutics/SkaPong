#include "StateTerminalPath.h"
#include "LetterDeleterSystem.h"

StateTerminalPath::StateTerminalPath(ska::StateData<ska::EntityManager, TerminalGameEventDispatcher>& data, ska::StateHolder& sh, GUI& gui, LetterDeleterSystem& letterDeleterSystem, ska::Rectangle& screenBox) :
	StateBase<ska::EntityManager, ska::ExtensibleGameEventDispatcher<TerminalGUIEvent>>(data.m_entityManager, data.m_eventDispatcher, sh),
	m_letterDeleterSystem(letterDeleterSystem),
	m_screenBox(screenBox) {
}


void StateTerminalPath::onEventUpdate(unsigned int ellapsedTime) {
	static unsigned int cummuledEllapsedTime = 2000;

	if (cummuledEllapsedTime > 100) {
		cummuledEllapsedTime = 0;
		if (ska::NumberUtils::random(0, 2) == 0) {
			if (m_letterDeleterSystem.getTotalEnemy() < 40) {
				m_letterDeleterSystem.createEnemy(m_screenBox);
			}
		} else if (ska::NumberUtils::random(0, 2) == 0 && m_letterDeleterSystem.getTotalLetter() < 15) {
			m_letterDeleterSystem.createLetter(m_screenBox);
		}
	}
	cummuledEllapsedTime += ellapsedTime;
}

void StateTerminalPath::onGraphicUpdate(unsigned int, ska::DrawableContainer&) {
	
}
