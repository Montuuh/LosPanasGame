#include "ItemDiamond.h"

#include "App.h"
#include "ModuleCollisions.h"


ItemDiamond::ItemDiamond(int x, int y) : Entity(x, y)
{
	spawnDelay = 0;

	anim.PushBack({ 560,817,15,13 });
	currentAnim = &anim;

	collider = app->collisions->AddCollider({ 1, 0, 13, 10 }, Collider::Type::ITEM, (Module*)app->entities, Collider::Items::DIAMOND);
}

void ItemDiamond::Update(float dt)
{

	Entity::Update(dt);
}