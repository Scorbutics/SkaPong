#pragma once
#include "ECS/SerializableComponent.h"

struct BossEnemyComponent :
	public ska::SerializableComponent {
	std::vector<ska::Point<int>> spawnPoint;
};
