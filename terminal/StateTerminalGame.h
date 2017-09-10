#pragma once
#include "ECS/EntityManager.h"
#include "Core/State/StateBase.h"
#include "Data/Events/ExtensibleGameEventDispatcher.h"
#include "Physic/System/EntityCollisionResponse.h"
#include "EnemyAllyCollisionResponse.h"
#include "AI.h"
#include "FadeBackgroundRenderer.h"
#include "../../ska/ska_particle/ParticleSystem.h"
#include "LetterDeleterSystem.h"
#include "CountdownTimeEventListener.h"
#include "StateTerminalPath.h"
#include <type_traits>

class GUI;

class StateTerminalGame :
	public ska::StateBase<ska::EntityManager, TerminalGameEventDispatcher> {
public:
	StateTerminalGame(StateData& data, ska::StateHolder& sh, GUI& gui, unsigned int windowWidth, unsigned int windowHeight);
	virtual void onEventUpdate(unsigned int ellapsedTime) override;
	virtual ~StateTerminalGame() = default;

protected:
	void onGraphicUpdate(unsigned, ska::DrawableContainer&) override;

private:
	ska::CameraSystem* m_cameraSystem;
	TerminalGameEventDispatcher& m_eventDispatcher;
	ska::EntityManager& m_entityManager;

	std::unique_ptr<ska::EntityCollisionResponse> m_entityCollision;
	ska::EntityId m_ball;
	std::unique_ptr<EnemyAllyCollisionResponse> m_scoreMaker;
	AI m_ai;
	ska::Rectangle m_screenBox;
	ska::EntityId m_enemyBar;
	GUI& m_gui;

	FadeBackgroundRenderer m_fadeBackgroundRenderer;
	ska::ParticleSystem m_particleSystem;
	LetterDeleterSystem* m_letterDeleterSystem;
	CountdownTimeEventListener m_countdown;

	ska::Texture m_scrollingBackgrounImage;
	State* m_currentSubState;
	ska::EntityId m_poa;
};
