#pragma once
#include "GUI/GUI.h"

class GUI : 
	public ska::GUI {
public:
	explicit GUI(ska::GameEventDispatcher& ged);
	virtual ~GUI() = default;
};
