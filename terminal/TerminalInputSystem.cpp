#include "TerminalInputSystem.h"
#include "Inputs/InputAction.h"
#include "Inputs/InputContextManager.h"

TerminalInputSystem::TerminalInputSystem(ska::EntityManager& entityManager, ska::GameEventDispatcher& ged, ska::EntityId& pointOfAttraction) :
	System(entityManager),
	ska::SubObserver<ska::InputKeyEvent>(std::bind(&TerminalInputSystem::onKeyInputEvent, this, std::placeholders::_1), ged),
	m_eventDispatcher(ged),
	m_poa(pointOfAttraction) {
}

void TerminalInputSystem::refresh(unsigned int) {
}

bool TerminalInputSystem::onKeyInputEvent(ska::InputKeyEvent& ike) {
	static const auto forceRadius = 27.F;
	static const auto spreadRadius = 20.F;
	static const auto maxDistanceSquared = 150 * 150;

	const auto& icm = ike.icm;
	const auto& processed = getEntities();

	const auto& spreadingAngle = processed.empty() ? 0.0 : 2 * M_PI / processed.size();
	const auto& pcPoa = m_componentAccessor.get<ska::PositionComponent>(m_poa);

	std::size_t index = 0;
	for (const auto& entityId : processed) {
		auto& forceComponent = m_componentAccessor.get<ska::ForceComponent>(entityId);
		auto& pc = m_componentAccessor.get<ska::PositionComponent>(entityId);
	
		const auto& iac = icm.getActions();
		auto& mousePos = ike.icm.getRanges()[ska::MousePos];

		if (iac[ska::Jump]) {
			const ska::Point<int> diffPoa(pcPoa.x - pc.x, pcPoa.y - pc.y);
			if (diffPoa.x * diffPoa.x + diffPoa.y * diffPoa.y > maxDistanceSquared) {
				continue;
			}
			const ska::Point<int> diff(pc.x - mousePos.x, pc.y - mousePos.y);
			const auto& angle = static_cast<float>(ska::NumberUtils::arctan(diff.x, diff.y));

			const auto finalAccelerationPoint = ska::Point<float>::cartesian(forceRadius, angle);
			forceComponent.x -= finalAccelerationPoint.x;
			forceComponent.y -= finalAccelerationPoint.y;
		} else if(iac[ska::DoAction]) {
			ska::PolarPoint<float> pp;
			pp.angle = spreadingAngle * index;
			pp.radius = spreadRadius;

			const auto finalAccelerationPoint = ska::Point<float>::cartesian(pp.radius, pp.angle);
			forceComponent.x += finalAccelerationPoint.x;
			forceComponent.y += finalAccelerationPoint.y;
		}
		index++;
	}
	return true;
}
