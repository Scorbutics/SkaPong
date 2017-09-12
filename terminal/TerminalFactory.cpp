#include "TerminalFactory.h"
#include "Graphic/AnimatedTexture.h"
#include "Graphic/GraphicComponent.h"
#include "ECS/EntityManager.h"
#include "ECS/Basics/Physic/GravityAffectedComponent.h"
#include "ECS/Basics/Physic/MovementComponent.h"
#include "ECS/Basics/Physic/PositionComponent.h"
#include "ECS/Basics/Physic/CollidableComponent.h"
#include "ECS/Basics/Physic/ForceComponent.h"
#include "Game.h"
#include "CharacterComponent.h"
#include "EnemyComponent.h"
#include "ECS/Basics/Graphic/DeleterComponent.h"
#include "BossEnemyComponent.h"

const std::string& RESOURCES_FOLDER = "." FILE_SEPARATOR "Resources" FILE_SEPARATOR;

const char* DICTIONNARY[] = {
	"root",
	"ls",
	"cd",
	"C:\\",
	"dir",
	"exe",
	"bin",
	"0101",
	"cmd",
	"int21h"
};

//factory
ska::EntityId TerminalFactory::createAsciiCharacterEntity(ska::EntityManager& m_entityManager, ska::Point<float> pos) {
	
	auto entity = m_entityManager.createEntity();
	ska::GraphicComponent gc;
	ska::Texture at;

	auto letter = static_cast<char>(ska::NumberUtils::random('0', '1'));
	auto randomColor = Game::COLOR_PALET[ska::NumberUtils::random(0, 9 - 1)];

	at.loadFromText(24, ska::StringUtils::charToStr(letter), ska::Color(randomColor));
	gc.sprites.push_back(at);
	m_entityManager.addComponent<ska::GraphicComponent>(entity, std::move(gc));
	m_entityManager.addComponent<ska::GravityAffectedComponent>(entity, ska::GravityAffectedComponent());

	ska::MovementComponent mc;
	mc.ay = 20.F;
	m_entityManager.addComponent<ska::MovementComponent>(entity, std::move(mc));
	ska::PositionComponent pc;
	pc.x = pos.x;
	pc.y = pos.y;
	pc.z = 0;
	m_entityManager.addComponent<ska::PositionComponent>(entity, std::move(pc));

	m_entityManager.addComponent<ska::CollidableComponent>(entity, ska::CollidableComponent());
	ska::HitboxComponent hc;
	hc.height = at.getHeight();
	hc.width = at.getWidth();
	m_entityManager.addComponent<ska::HitboxComponent>(entity, std::move(hc));

	ska::ForceComponent fc;
	fc.bounciness = 1.F;
	fc.weight = 1.F;
	m_entityManager.addComponent<ska::ForceComponent>(entity, std::move(fc));
	
	//Tag
	m_entityManager.addComponent<CharacterComponent>(entity, CharacterComponent());

	ska::DeleterComponent dc;
	dc.delay = 15000;
	dc.startTime = ska::TimeUtils::getTicks();
	m_entityManager.addComponent(entity, std::move(dc));

	return entity;
}

ska::EntityId TerminalFactory::createBaseEnemyStringEntity(ska::EntityManager& m_entityManager) {
	auto entity = m_entityManager.createEntity();
	ska::GraphicComponent gc;
	ska::Texture at;

	auto randomColor = Game::COLOR_PALET[ska::NumberUtils::random(0, 9 - 1)];
	EnemyComponent ec;
	ec.life = 10;
	m_entityManager.addComponent<EnemyComponent>(entity, std::move(ec));

	at.loadFromText(ec.life / 10.F * 32, DICTIONNARY[ska::NumberUtils::random(0, 9)], ska::Color(randomColor));
	gc.sprites.push_back(at);
	m_entityManager.addComponent<ska::GraphicComponent>(entity, std::move(gc));
	ska::GravityAffectedComponent gac;
	gac.friction = 0.F;
	m_entityManager.addComponent<ska::GravityAffectedComponent>(entity, std::move(gac));

	m_entityManager.addComponent<ska::CollidableComponent>(entity, ska::CollidableComponent());
	ska::HitboxComponent hc;
	hc.height = at.getHeight();
	hc.width = at.getWidth();
	m_entityManager.addComponent<ska::HitboxComponent>(entity, std::move(hc));

	ska::ForceComponent fc;
	fc.bounciness = 1.F;
	fc.weight = std::numeric_limits<float>::max();
	m_entityManager.addComponent<ska::ForceComponent>(entity, std::move(fc));

	ska::DeleterComponent dc;
	dc.delay = 15000;
	dc.startTime = ska::TimeUtils::getTicks();
	m_entityManager.addComponent(entity, std::move(dc));

	return entity;
}

ska::EntityId TerminalFactory::createEnemyStringEntity(ska::EntityManager& m_entityManager, ska::Rectangle& screenBox) {
	auto entity = createBaseEnemyStringEntity(m_entityManager);

	auto& gc = m_entityManager.getComponent<ska::GraphicComponent>(entity);
	auto& at = gc.sprites[0];

	ska::MovementComponent mc;
	ska::PositionComponent pc;
	if (ska::NumberUtils::random(0, 1)) {
		pc.x = (ska::NumberUtils::random(0, screenBox.w) - at.getWidth() - 10);
		pc.y = 10;
		mc.vy = 5.F;
	} else {
		bool left = ska::NumberUtils::random(0, 1);
		pc.x = left ? 10 : screenBox.w;
		pc.y = (ska::NumberUtils::random(0, screenBox.h) - at.getHeight() - 10);
		mc.vx = left ? 5.F : -5.F;
	}
	pc.z = 0;
	m_entityManager.addComponent<ska::MovementComponent>(entity, std::move(mc));
	m_entityManager.addComponent<ska::PositionComponent>(entity, std::move(pc));
	return entity;
}

ska::EntityId TerminalFactory::createBossEnemyStringEntity(ska::EntityManager& m_entityManager, ska::Point<int>& pos, ska::EntityId poa) {
	auto entity = createBaseEnemyStringEntity(m_entityManager);

	ska::MovementComponent mc;
	ska::PositionComponent pc;
	pc.x = pos.x;
	pc.y = pos.y;
	pc.z = 0;

	auto& poaPos = m_entityManager.getComponent<ska::PositionComponent>(poa);
	ska::Point<float> diff(pos.x - poaPos.x, pos.y - poaPos.y);
	const auto& pp = ska::PolarPoint<float>::polar(diff.x, diff.y);
	const auto& resultPoint = ska::Point<float>::cartesian(5.F, pp.angle);
	
	mc.vx -= resultPoint.x;
	mc.vy -= resultPoint.y;

	m_entityManager.addComponent<ska::MovementComponent>(entity, std::move(mc));
	m_entityManager.addComponent<ska::PositionComponent>(entity, std::move(pc));

	auto& ec = m_entityManager.getComponent<EnemyComponent>(entity);
	ec.createdFromBoss = true;

	return entity;
}

ska::EntityId TerminalFactory::createTopAndBottomBoundaries(ska::EntityManager& m_entityManager, int pos, ska::Rectangle screenBox) {
	auto entity = m_entityManager.createEntity();
	m_entityManager.addComponent<ska::GravityAffectedComponent>(entity, ska::GravityAffectedComponent());

	ska::MovementComponent mc;
	m_entityManager.addComponent<ska::MovementComponent>(entity, std::move(mc));

	m_entityManager.addComponent<ska::CollidableComponent>(entity, ska::CollidableComponent());
	ska::HitboxComponent hc;
	hc.height = pos == 1 || pos == 3 ? screenBox.h : 10;
	hc.width = pos == 0 || pos == 2 ? screenBox.w : 10;
	
	ska::PositionComponent pc;
	pc.x = pos == 1 ? -static_cast<int>(0) : (pos == 3 ? screenBox.w - hc.width : 0);
	pc.y = pos == 0 ? -static_cast<int>(0) : (pos == 2 ? screenBox.h - hc.height : 0);
	pc.z = 0;
	
	m_entityManager.addComponent<ska::PositionComponent>(entity, std::move(pc));
	m_entityManager.addComponent<ska::HitboxComponent>(entity, std::move(hc));

	ska::ForceComponent fc;
	fc.weight = std::numeric_limits<float>::max();
	m_entityManager.addComponent<ska::ForceComponent>(entity, std::move(fc));

	return entity;
}

ska::EntityId TerminalFactory::createPointOfAttraction(ska::EntityManager& entityManager, const ska::Point<int>& pos) {
	auto entity = entityManager.createEntity();
	
	ska::GraphicComponent gc;
	ska::AnimatedTexture at;
	at.load("Resources/Sprites/0.png", 2, 1, 2);
	at.setDelay(500);
	gc.animatedSprites.push_back(at);

	entityManager.addComponent<ska::CollidableComponent>(entity, ska::CollidableComponent());
	ska::HitboxComponent hc;
	hc.height = gc.animatedSprites[0].getHeight();
	hc.width = gc.animatedSprites[0].getWidth();
	entityManager.addComponent<ska::HitboxComponent>(entity, std::move(hc));

	entityManager.addComponent<ska::GraphicComponent>(entity, std::move(gc));

	ska::GravityAffectedComponent gac;
	gac.friction = std::numeric_limits<float>::max()*0.03F;
	entityManager.addComponent<ska::GravityAffectedComponent>(entity, std::move(gac));
	
	ska::ForceComponent fc;
	fc.bounciness = 0;
	fc.weight = std::numeric_limits<float>::max();
	entityManager.addComponent<ska::ForceComponent>(entity, std::move(fc));
	
	ska::MovementComponent mc;
	entityManager.addComponent<ska::MovementComponent>(entity, std::move(mc));

	ska::PositionComponent pc;
	pc.x = pos.x;
	pc.y = pos.y;
	pc.z = 0;
	entityManager.addComponent<ska::PositionComponent>(entity, std::move(pc));

	return entity;
}

ska::EntityId TerminalFactory::createEnemyBossEntity(ska::EntityManager& entityManager, const ska::Rectangle& screenBox) {
	auto entity = entityManager.createEntity();
	ska::GraphicComponent gc;
	ska::Texture at;

	EnemyComponent ec;
	ec.life = 700;
	ec.dieOnBorder = false;
	entityManager.addComponent<EnemyComponent>(entity, std::move(ec));

	at.loadFromText(96, "§BUG§", ska::Color(0xFF, 0xFF, 0xFF, 0xFF));
	gc.sprites.push_back(at);
	entityManager.addComponent<ska::GraphicComponent>(entity, std::move(gc));

	ska::GravityAffectedComponent gac;
	gac.friction = std::numeric_limits<float>::max()*0.03F;
	entityManager.addComponent<ska::GravityAffectedComponent>(entity, std::move(gac));
	
	ska::MovementComponent mc;
	
	ska::PositionComponent pc;
	pc.x = screenBox.w / 2 - at.getWidth() / 2;
	pc.y = -10;
	pc.z = 0;

	BossEnemyComponent bec;
	bec.spawnPoint.push_back(ska::Point<int>(pc.x - 150, 150));
	bec.spawnPoint.push_back(ska::Point<int>(screenBox.w / 2 + at.getWidth() / 2 + 10, 150));
	entityManager.addComponent<BossEnemyComponent>(entity, std::move(bec));

	entityManager.addComponent<ska::MovementComponent>(entity, std::move(mc));
	entityManager.addComponent<ska::PositionComponent>(entity, std::move(pc));
	entityManager.addComponent<ska::CollidableComponent>(entity, ska::CollidableComponent());
	
	ska::HitboxComponent hc;
	hc.height = at.getHeight();
	hc.width = at.getWidth();
	entityManager.addComponent<ska::HitboxComponent>(entity, std::move(hc));

	ska::ForceComponent fc;
	fc.bounciness = 1.F;
	fc.weight = std::numeric_limits<float>::max();
	entityManager.addComponent<ska::ForceComponent>(entity, std::move(fc));

	return entity;
}
