#pragma once
#include "ECS/ECSDefines.h"

namespace ska {
	class EntityManager;
}

class AI {
public:
	explicit AI(ska::EntityManager& em);
	
	void update(ska::EntityId enemyBar, ska::EntityId ball) const;

	~AI() = default;
private:
	ska::EntityManager& m_entityManager;

};
