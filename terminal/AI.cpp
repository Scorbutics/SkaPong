#include "AI.h"
#include "ECS/Basics/Physic/PositionComponent.h"
#include "ECS/EntityManager.h"
#include "Utils/RectangleUtils.h"
#include "ECS/Basics/Physic/MovementComponent.h"

#define THRESHOLD_DISTANCE_BAR_BALL 25

AI::AI(ska::EntityManager & em) :
	m_entityManager(em) {
}

void AI::update(ska::EntityId enemyBar, ska::EntityId ball) const{
	ska::Point<float> pcEnemy = m_entityManager.getComponent<ska::PositionComponent>(enemyBar);
	ska::Point<float> pcBall = m_entityManager.getComponent<ska::PositionComponent>(ball);

	auto& fEnemy = m_entityManager.getComponent<ska::MovementComponent>(enemyBar);

	if(ska::NumberUtils::absolute(pcEnemy.y - pcBall.y) >= ska::NumberUtils::random(0, 100) + THRESHOLD_DISTANCE_BAR_BALL) {
		fEnemy.vy += (pcBall.y - pcEnemy.y) * 0.005F;
	}
}
