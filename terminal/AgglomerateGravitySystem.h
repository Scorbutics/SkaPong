#pragma once
#include <unordered_set>
#include "ECS/System.h"
#include "ECS/Basics/Physic/ForceComponent.h"
#include "ECS/Basics/Physic/PositionComponent.h"
#include "ECS/Basics/Physic/GravityAffectedComponent.h"
#include "ECS/Basics/Physic/CollidableComponent.h"
#include "CharacterComponent.h"

class AgglomerateGravitySystem : public ska::System<std::unordered_set<ska::EntityId>, ska::RequiredComponent<ska::ForceComponent, ska::PositionComponent, CharacterComponent>, ska::PossibleComponent<>> {
public:
	AgglomerateGravitySystem(ska::EntityManager& entityManager, ska::EntityId& pointOfAttraction);
	AgglomerateGravitySystem& operator=(const AgglomerateGravitySystem&) = delete;
	virtual ~AgglomerateGravitySystem();
protected:
	
	virtual void refresh(unsigned int ellapsedTime) override;

	ska::EntityId m_pointOfAttraction;
};

