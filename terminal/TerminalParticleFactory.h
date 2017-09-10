#pragma once

namespace ska {
	class ParticleSystem;
}

class TerminalParticleFactory {
public:
	static void createStarsBackground(ska::ParticleSystem& m_particleSystem, unsigned int windowWidth, unsigned int windowHeight);
};