#pragma once
#include "Data/Events/ExtensibleGameEventDispatcher.h"
#include "TerminalGUIEvent.h"

using TerminalGameEventDispatcher = ska::ExtensibleGameEventDispatcher<TerminalGUIEvent>;
