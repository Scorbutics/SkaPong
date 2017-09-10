#include "TerminalParticleFactory.h"
#include "../../ska/ska_particle/Impl/GenerationDelayProperty.h"
#include "Draw/SDLRenderer.h"
#include "../../ska/ska_particle/Impl/SpreadingColorParticleEffectFactory.h"
#include "Game.h"
#include "../../ska/ska_particle/Impl/SpreadingParticleEffectFactory.h"
#include "../../ska/ska_particle/ParticleSystem.h"

void TerminalParticleFactory::createStarsBackground(ska::ParticleSystem& m_particleSystem, unsigned int windowWidth, unsigned int windowHeight) {
	ska::Color cEnd(Game::COLOR_PALET[2]);
	ska::Color cStart(Game::COLOR_PALET[3]);
	ska::SpreadingParticleSystemData effectData;
	effectData.lifetime = 2000;
	effectData.origin.x = windowWidth / 2;
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
	effect.applyGroupProperty<ska::GenerationDelayProperty>(effectData.lifetime / 200);
	
}
