#include "AgglomerateGravitySystem.h"
#include "ECS/Basics/Physic/PositionComponent.h"
#include "Utils/RectangleUtils.h"

AgglomerateGravitySystem::AgglomerateGravitySystem(ska::EntityManager& entityManager, ska::EntityId& pointOfAttraction) : 
	System(entityManager),
	m_pointOfAttraction(pointOfAttraction) {
}

void AgglomerateGravitySystem::refresh(unsigned int) {
	const static auto forceRadius = 200.F;
	const auto& processed = getEntities();
	auto& pcTargetComponent = m_componentAccessor.get<ska::PositionComponent>(m_pointOfAttraction);

	for (auto entityId : processed) {
		if(m_pointOfAttraction == entityId) {
			continue;
		}

		auto& forceComponent = m_componentAccessor.get<ska::ForceComponent>(entityId);
		auto& pc = m_componentAccessor.get<ska::PositionComponent>(entityId);
		
		const ska::Point<int> diff(pc.x - pcTargetComponent.x, pc.y - pcTargetComponent.y);
		const auto& angle = static_cast<float>(ska::NumberUtils::arctan(diff.x, diff.y));
		
		auto diffDistance = ska::NumberUtils::squareroot(diff.x * diff.x + diff.y * diff.y);

		ska::Point<float> finalAccelerationPoint;
		//Not engouh far away, we don't attract at all !
		if(diffDistance < 75.F) {
			finalAccelerationPoint.x = 0;
			finalAccelerationPoint.y = 0;
		} else {
			finalAccelerationPoint = ska::Point<float>::cartesian(forceRadius / diffDistance, angle);
		}

		//Too far away, we don't attract at all !
		if (ska::NumberUtils::absolute(finalAccelerationPoint.x) < 0.25 
			&& ska::NumberUtils::absolute(finalAccelerationPoint.y) < 0.25) {
			finalAccelerationPoint.x = 0;
			finalAccelerationPoint.y = 0;
		}

		forceComponent.x -= finalAccelerationPoint.x;
		forceComponent.y -= finalAccelerationPoint.y;
	}
}

AgglomerateGravitySystem::~AgglomerateGravitySystem() {
}
