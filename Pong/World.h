#pragma once
#include "ECS/Basics/Physic/CollisionProfile.h"

class World : 
	public ska::CollisionProfile {
public:
	World(unsigned int width, unsigned int height);
	virtual ~World() override = default;
	virtual bool intersectBlocksAtPos(const ska::Rectangle& hitbox, std::vector<ska::Point<int>>& outputX, std::vector<ska::Point<int>>& outputY) const override;
	virtual bool isBlockAuthorizedAtPos(const ska::Point<int>& pos, const std::unordered_set<int>& blocksAuthorized) const override;
private:
	const unsigned int m_width;
	const unsigned int m_height;

};
