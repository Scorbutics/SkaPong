#pragma once
#include "ECS/Component.h"

struct EnemyComponent : public ska::Component {
	EnemyComponent() : 
		life(0) {
	}
	int life;
};
