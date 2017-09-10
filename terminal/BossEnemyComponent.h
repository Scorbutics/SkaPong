#pragma once
#include "ECS/Component.h"

struct BossEnemyComponent :
	public ska::Component {
	std::vector<ska::Point<int>> spawnPoint;
};
