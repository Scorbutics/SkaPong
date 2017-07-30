#pragma once
#include "ECS/ECSDefines.h"
#include "ECS/EntityManager.h"
#include "Rectangle.h"
#include "Point.h"

class PongFactory {
private:
	PongFactory() = default;

public:
	static ska::EntityId createPongBarEntity(ska::EntityManager& m_entityManager, ska::Point<float> pos);
	static ska::EntityId createPongBallEntity(ska::EntityManager& m_entityManager, ska::Point<float> pos);
	static ska::EntityId createTopAndBottomBoundaries(ska::EntityManager& m_entityManager, bool top, ska::Rectangle screenBox);

	~PongFactory() = default;
	
};
