#pragma once
#include "CountdownTimeEventListener.h"
#include "Point.h"
#include "GUI/Components/Concrete/Label.h"
#include "GUI/Windows/DynamicWindowIG.h"
#include "TerminalGUIEvent.h"
#include "GUI.h"
#include "Utils/StringUtils.h"
#include "Exceptions/TerminateProcessException.h"

CountdownTimeEventListener::CountdownTimeEventListener(TerminalGameEventDispatcher& ged, GUI& gui, const ska::Rectangle& screenBox) :
	ska::SubObserver<TerminalGUIEvent>(std::bind(&CountdownTimeEventListener::onTerminalGUIUpdateEvent, this, std::placeholders::_1), ged), m_score(0), m_currentTime(0),
	m_gui(gui), m_scoreLabel(nullptr), m_timeLabel(nullptr){
	const auto& theme = std::string("." FILE_SEPARATOR "Resources" FILE_SEPARATOR "Menu" FILE_SEPARATOR "start_screen_theme" FILE_SEPARATOR);

	auto scoreboard = &m_gui.addWindow<ska::DynamicWindowIG<>>("scoreboardWindow", ska::Rectangle{15, 1, screenBox.w - 50, 50}, theme + "menu");
	ska::Point<int> buttonPos(3, 1);
	buttonPos.x += 100;
	
	m_scoreLabel = &scoreboard->addWidget<ska::Label>("0", 36, ska::Point<int>(buttonPos.x, buttonPos.y + 10));
	m_scoreLabel->setFontColor(255, 255, 255, 255);
	buttonPos.x += 200;
	
	m_timeLabel = &scoreboard->addWidget<ska::Label>("2:00", 36, ska::Point<int>(buttonPos.x, buttonPos.y + 10));
	m_timeLabel->setFontColor(255, 255, 255, 255);
}

std::string ConvertToMinutesDisplay(long time) {
	const auto& totalSeconds = time / 1000;
	const auto& realSeconds = totalSeconds % 60;
	const auto& minutes = totalSeconds / 60;
	return ska::StringUtils::intToStr(minutes) + ":" + (realSeconds < 10 ? "0" : "") + ska::StringUtils::intToStr(realSeconds);
}

bool CountdownTimeEventListener::onTerminalGUIUpdateEvent(TerminalGUIEvent& tge) {
	switch(tge.type) {
	case UPDATE_SCORE:
		m_score += tge.score;
		m_scoreLabel->modifyText(ska::StringUtils::intToStr(m_score));
		break;
	case UPDATE_TIME:
		m_currentTime += tge.time;
		auto remainingTime = 2 * 60 * 1000L - m_currentTime;
		if (remainingTime < 0) {
			throw ska::TerminateProcessException("time over");
		}
		m_timeLabel->modifyText(ConvertToMinutesDisplay(remainingTime));
		break;
	}
	return true;
}
