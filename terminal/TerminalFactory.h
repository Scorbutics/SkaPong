#pragma once
#include "ECS/ECSDefines.h"
#include "ECS/EntityManager.h"
#include "Rectangle.h"
#include "Point.h"

class TerminalFactory {
private:
	TerminalFactory() = default;

public:
	static ska::EntityId createAsciiCharacterEntity(ska::EntityManager& m_entityManager, ska::Point<float> pos);
	static ska::EntityId createEnemyStringEntity(ska::EntityManager& m_entityManager, ska::Rectangle& screenBox);
	static ska::EntityId createTopAndBottomBoundaries(ska::EntityManager& m_entityManager, int top, ska::Rectangle screenBox);
	static ska::EntityId createPointOfAttraction(ska::EntityManager& entity_manager, const ska::Point<int>& point);

	~TerminalFactory() = default;

};
