#include "World.h"

World::World(unsigned int width, unsigned int height):
	m_width(width),
	m_height(height) {
}

bool World::intersectBlocksAtPos(const ska::Rectangle& hitbox, std::vector<ska::Point<int>>& outputX, std::vector<ska::Point<int>>& outputY) const {
	auto intersected = false;
	if(hitbox.x < 0 || hitbox.x + hitbox.w > m_width) {
		outputX.push_back(hitbox);
		intersected = true;
	}

	if(hitbox.y < 0 || hitbox.y + hitbox.h > m_height) {
		outputY.push_back(hitbox);
		intersected = true;
	}
	return intersected;
}

bool World::isBlockAuthorizedAtPos(const ska::Point<int>& pos, const std::unordered_set<int>& blocksAuthorized) const {
	return false;
}
