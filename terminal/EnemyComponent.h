#pragma once
#include "ECS/Component.h"
#include "EnemyAllyCollisionResponse.h"

struct EnemyComponent : public ska::Component {
	EnemyComponent() : 
		life(0),
		dieOnBorder(true),
		createdFromBoss(false) {
	}
	int life;
	bool dieOnBorder;
	bool createdFromBoss;
};
