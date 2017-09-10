#pragma once
#include "Core/GameCore.h"
#include "ECS/EntityManager.h"
#include "Draw/VectorDrawableContainer.h"
#include "Audio/SoundRenderer.h"
#include "GUI.h"
#include "TerminalGameEventDispatcher.h"
#include "Audio/Music.h"

using GameBase = ska::GameCore<ska::EntityManager, TerminalGameEventDispatcher, ska::VectorDrawableContainer, ska::SoundRenderer>;
class Game : 
	public GameBase {

public:
	Game();
	void init();
	virtual ~Game() = default;

	static const Uint32 COLOR_PALET[];

private:
	int onTerminate(ska::TerminateProcessException & tpe) override;
	int onException(ska::GenericException & e) override;

	std::unique_ptr<GUI> m_gui;
	ska::Music m_backgroundMusic;
};
