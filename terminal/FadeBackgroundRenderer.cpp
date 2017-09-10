#include "FadeBackgroundRenderer.h"
#include "Utils/NumberUtils.h"
#include "Game.h"

FadeBackgroundRenderer::FadeBackgroundRenderer(): 
	m_color(0x000000FF), 
	m_cummulatedTime(10000), 
	m_nextColor(0x000000FF) {
}

void FadeBackgroundRenderer::render(unsigned ellapsedTime){
	m_cummulatedTime += ellapsedTime;
	auto percentsTimeEllapsed = m_cummulatedTime / 10000.0;
	if (percentsTimeEllapsed >= 1.F) {
		m_cummulatedTime = 0;
		percentsTimeEllapsed = 0.0F;
		m_color = m_nextColor;
		m_nextColor = Game::COLOR_PALET[ska::NumberUtils::random(0, 9 - 1)];
	}
	ska::Color next(m_nextColor);
	ska::Color current(m_color);
	const auto r = percentsTimeEllapsed * (next.r - current.r) + current.r;
	const auto g = percentsTimeEllapsed * (next.g - current.g) + current.g;
	const auto b = percentsTimeEllapsed * (next.b - current.b) + current.b;

	static const auto maxIntensity = 5.F;
	ska::SDLRenderer::getDefaultRenderer()->setRenderColor(ska::Color(r / maxIntensity, g / maxIntensity, b / maxIntensity, 0xFF));
}

