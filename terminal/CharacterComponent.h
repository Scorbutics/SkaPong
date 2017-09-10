#pragma once

struct CharacterComponent : public ska::Component {
	CharacterComponent() : life(1) {}
	int life;
};