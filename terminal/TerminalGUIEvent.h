#pragma once

enum TerminalGUIEventType {
	UPDATE_TIME,
	UPDATE_SCORE
};

struct TerminalGUIEvent {
	explicit TerminalGUIEvent(const TerminalGUIEventType& tget) : 
		score(0), 
		time(0), 
		type(tget) {
	}

	int score;
	long time;

	const TerminalGUIEventType type;
};