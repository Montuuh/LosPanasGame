#include "ItemHealth.h"

#include "App.h"
#include "ModuleCollisions.h"


ItemHealth::ItemHealth(int x, int y) : Entity(x, y)
{
	spawnDelay = 0;
	this->entityType = EntityType::ITEM_HEALTH;
	anim.PushBack({ 419,400,10,16 });
	currentAnim = &anim;

	collider = app->collisions->AddCollider({1, 0, 8 , 16 }, Collider::Type::ITEM, (Module*) app->entities, Collider::Items::HEALTH);
}

void ItemHealth::Update(float dt)
{
	Entity::Update(dt);
}
