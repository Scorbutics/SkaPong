#pragma once

struct CharacterComponent : public ska::SerializableComponent {
	CharacterComponent() : life(1) {}
	int life;
};