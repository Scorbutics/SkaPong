#pragma once
#include <SDL_hints.h>

class FadeBackgroundRenderer {
public:
	FadeBackgroundRenderer();
	void render(unsigned ellapsedTime);
	~FadeBackgroundRenderer() = default;

private:
	Uint32 m_color;
	unsigned int m_cummulatedTime;
	Uint32 m_nextColor;
};
