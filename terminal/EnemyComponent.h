#pragma once
#include "ECS/SerializableComponent.h"
#include "EnemyAllyCollisionResponse.h"

struct EnemyComponent : public ska::SerializableComponent {
	EnemyComponent() : 
		life(0),
		dieOnBorder(true),
		createdFromBoss(false) {
	}
	int life;
	bool dieOnBorder;
	bool createdFromBoss;
};
