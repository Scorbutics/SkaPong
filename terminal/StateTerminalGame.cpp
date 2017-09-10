#include "StateTerminalGame.h"
#include "Graphic/System/GraphicSystem.h"
#include "Graphic/System/CameraFixedSystem.h"
#include "Physic/System/MovementSystem.h"
#include "Physic/System/CollisionSystem.h"
#include "Physic/System/GravitySystem.h"
#include "Inputs/System/InputSystem.h"
#include "TerminalFactory.h"
#include "EnemyAllyCollisionResponse.h"
#include "Draw/SDLRenderer.h"
#include "AgglomerateGravitySystem.h"
#include "GUI.h"
#include "Draw/DrawableContainer.h"
#include "TerminalInputSystem.h"
#include "../../ska/ska_particle/Impl/SpreadingColorParticleEffectFactory.h"
#include "../../ska/ska_particle/Impl/SpreadingParticleEffectFactory.h"
#include "../../ska/ska_particle/Impl/GenerationDelayProperty.h"
#include "Game.h"
#include "LetterDeleterSystem.h"

StateTerminalGame::StateTerminalGame(StateData& data, ska::StateHolder & sh, GUI& gui, unsigned int windowWidth, unsigned int windowHeight) :
	StateBase(data.m_entityManager, data.m_eventDispatcher, sh),
	m_cameraSystem(nullptr),
	m_eventDispatcher(data.m_eventDispatcher),
	m_entityManager(data.m_entityManager),
	m_entityCollision(data.m_eventDispatcher, data.m_entityManager),
	m_ai(data.m_entityManager),
	m_gui(gui),
	m_countdown(data.m_eventDispatcher, m_gui, ska::Rectangle{ 0, 0, static_cast<int>(windowWidth), static_cast<int>(windowHeight) }) {
	m_cameraSystem = addLogic<ska::CameraFixedSystem>(windowWidth, windowHeight, ska::Point<int>());
	addGraphic<ska::GraphicSystem>(m_eventDispatcher, m_cameraSystem);

	addLogic<ska::MovementSystem>();
	addLogic<ska::CollisionSystem>(m_eventDispatcher);
	//addLogic<ska::WorldCollisionSystem>(m_world, m_eventDispatcher);
	addLogic<ska::InputSystem>(m_eventDispatcher);

	m_screenBox = {0, 0, static_cast<int>(windowWidth), static_cast<int>(windowHeight)};

	auto blockA = TerminalFactory::createPointOfAttraction(m_entityManager, ska::Point<int>(windowWidth / 2, windowHeight / 2));
	TerminalFactory::createTopAndBottomBoundaries(m_entityManager, 0, m_screenBox);
	TerminalFactory::createTopAndBottomBoundaries(m_entityManager, 1, m_screenBox);
	TerminalFactory::createTopAndBottomBoundaries(m_entityManager, 2, m_screenBox);
	TerminalFactory::createTopAndBottomBoundaries(m_entityManager, 3, m_screenBox);

	addLogic<TerminalInputSystem>(m_eventDispatcher, blockA);
	addLogic<AgglomerateGravitySystem>(blockA);
	addLogic<ska::GravitySystem>();

	ska::InputComponent ic;
	//ic.movePower = 0.75F;
	ic.movePower = std::numeric_limits<float>::max() * 0.5F;
	m_entityManager.addComponent<ska::InputComponent>(blockA, std::move(ic));

	m_scoreMaker = std::make_unique<EnemyAllyCollisionResponse>(m_entityManager, m_eventDispatcher, *m_cameraSystem);
	
	addLogic<ska::DeleterSystem>();
	m_letterDeleterSystem = addLogic<LetterDeleterSystem>(m_eventDispatcher);

	ska::Color cEnd(Game::COLOR_PALET[2]);
	ska::Color cStart(Game::COLOR_PALET[3]);
	cEnd.a = 128;
	cStart.a = 128;
	ska::SpreadingParticleSystemData effectData;
	effectData.lifetime = 2000;
	effectData.origin.x = windowWidth/2;
	effectData.origin.y = -static_cast<int>(windowHeight) / 2;
	effectData.originalBoxSize.x = windowWidth / 2;
	effectData.originalBoxSize.y = windowHeight / 2;
	effectData.cStart = cStart;
	effectData.cEnd = cEnd;
	effectData.initialVelocity.radius = 7.5F;
	effectData.initialVelocity.angle = M_PI / 2.F;
	effectData.spreading = M_PI;
	effectData.spreadingSlices = 1;
	effectData.density = 15;
	effectData.maxParticles = 2000;
	effectData.randomVelocityMultiplier = 0.8F;
	auto& effect = m_particleSystem.makeEffect<ska::SpreadingColorParticleEffectFactory>(*ska::SDLRenderer::getDefaultRenderer(), effectData);
	effect.applyGroupProperty<ska::GenerationDelayProperty>(effectData.lifetime/200);
	
	m_scrollingBackgrounImage.load("Resources/Sprites/background.png");
}

void StateTerminalGame::onEventUpdate(unsigned int ellapsedTime) {
	static long totalEllapsedTime = 0;
	static unsigned int cummuledEllapsedTime = 2000;
	
	if(cummuledEllapsedTime > 100) {
		cummuledEllapsedTime = 0;
		if (ska::NumberUtils::random(0, 2) == 0) {
			if (m_letterDeleterSystem->getTotalEnemy() < 40) {
				m_letterDeleterSystem->createEnemy(m_screenBox);
			}
		} else if (ska::NumberUtils::random(0, 2) == 0 && m_letterDeleterSystem->getTotalLetter() < 15) {
			m_letterDeleterSystem->createLetter(m_screenBox);
		}
	}
	cummuledEllapsedTime += ellapsedTime;
	
	auto newTotalEllapsedTime = (totalEllapsedTime + ellapsedTime);
	if(newTotalEllapsedTime / 1000 != totalEllapsedTime / 1000) {
		TerminalGUIEvent tge(UPDATE_TIME);
		tge.time = 1000;
		m_eventDispatcher.ska::Observable<TerminalGUIEvent>::notifyObservers(tge);
	}
	
	totalEllapsedTime = newTotalEllapsedTime;
	
	m_gui.refresh(ellapsedTime);
	m_fadeBackgroundRenderer.render(ellapsedTime);
	m_particleSystem.refresh(ellapsedTime);
}

void StateTerminalGame::onGraphicUpdate(unsigned ellapsedTimes, ska::DrawableContainer& drawables) {
	static auto scrollingPos = 0.F;
	m_scrollingBackgrounImage.render(0, scrollingPos - m_scrollingBackgrounImage.getHeight() - 1);
	m_scrollingBackgrounImage.render(0, scrollingPos);
	scrollingPos += 0.17F;

	if(scrollingPos > m_scrollingBackgrounImage.getHeight()) {
		scrollingPos = 0;
	}

	m_particleSystem.display();
	drawables.addHead(m_gui);
	auto renderer = ska::SDLRenderer::getDefaultRenderer();

	ska::Color pureWhite(255, 255, 255, 255);
	renderer->drawColorLine(pureWhite, ska::Point<int>(), ska::Point<int>(0, m_screenBox.h));
	renderer->drawColorLine(pureWhite, ska::Point<int>(0, m_screenBox.h), ska::Point<int>(m_screenBox.w, m_screenBox.h));
	renderer->drawColorLine(pureWhite, ska::Point<int>(m_screenBox.w, m_screenBox.h), ska::Point<int>(m_screenBox.w, 0));
	renderer->drawColorLine(pureWhite, ska::Point<int>(m_screenBox.w, 0), ska::Point<int>());
}



