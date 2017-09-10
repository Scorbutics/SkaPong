#pragma once
#include "Rectangle.h"
#include "Utils/SubObserver.h"
#include "TerminalGameEventDispatcher.h"
#include "Core/Window.h"
#include "GUI/Components/Concrete/Label.h"

struct TerminalGUIEvent;
class GUI;

class CountdownTimeEventListener : 
	public ska::SubObserver<TerminalGUIEvent> {
public:
	CountdownTimeEventListener(TerminalGameEventDispatcher& ged, GUI& gui, const ska::Rectangle& screenBox);
	~CountdownTimeEventListener() = default;

private:
	bool onTerminalGUIUpdateEvent(TerminalGUIEvent& tge);
	
	int m_score;
	long m_currentTime;
	GUI& m_gui;

	ska::Label* m_scoreLabel;
	ska::Label* m_timeLabel;
};
