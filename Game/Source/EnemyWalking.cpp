//#include "EnemyWalking.h"
//
//#include "App.h"
//#include "ModuleCollisions.h"
//#include "Pathfinding.h"
//#include "ModulePlayer.h"
//#include "Map.h"
//#include "Render.h"
//#include "Input.h"
//
//#include "Log.h"
//
//#define SPEED_X 10.0f;
//#define SPEED_Y 5.0f;
//
//EnemyWalking::EnemyWalking(int x, int y) : Entity(x, y)
//{
//	spawnDelay = 0;
//
//	animLeft.PushBack({ 399,151,16,9 });
//	animLeft.PushBack({ 383,150,16,10 });
//	animLeft.speed = 0.1f;
//	animLeft.loop = true;
//
//	animRight.PushBack({ 416,151,16,9 });
//	animRight.PushBack({ 432,150,16,10 });
//	animRight.speed = 0.1f;
//	animRight.loop = true;
//
//	deathAnim.PushBack({ 448,153,15,7 });
//	deathAnim.loop = false;
//
//	currentAnim = &animLeft;
//
//	collider = app->collisions->AddCollider({ 0, 0, 16, 10 }, Collider::Type::ENEMY_HURTBOX, (Module*)app->entities, Collider::Items::ITEM_NONE);
//}
//
//void EnemyWalking::Update(float dt)
//{
//	Entity::Update(dt);
//
//	if (isDead)
//	{
//		currentAnim = &deathAnim;
//		this->collider->pendingToDelete = true;
//	}
//
//	if (path.Count() > 0)
//	{
//
//
//
//	}
//	else
//	{
//		direction = IDLE;
//		hasPath = false;
//	}
//
//	if (direction == IDLE)
//	{
//		entitySpeed = { 0 , 0 };
//	}
//
//	if (app->collisions->debug == true)
//	{
//		for (int i = 0; i < path.Count(); ++i)
//		{
//			iPoint pos = app->map->MapToWorld(path.At(i)->x, path.At(i)->y);
//			SDL_Rect r = { pos.x, pos.y, 16, 16 };
//			app->render->DrawRectangle(r, 155, 155, 155, 50);
//		}
//	}
//
//	if (!isDead)
//	{
//		position.x += entitySpeed.x * dt;
//		position.y += entitySpeed.y * dt;
//	}
//
//	collider->SetPos(position.x, position.y);
//}
//
//void EnemyWalking::SetVelDirection(DirectionState dir)
//{
//	if (dir == DOWN)
//	{
//		this->entitySpeed.y = SPEED_Y;
//	}
//	else if (dir == RIGHT)
//	{
//		goingRight = true;
//		this->entitySpeed.x = SPEED_X;
//	}
//	else if (dir == LEFT)
//	{
//		goingLeft = true;
//		this->entitySpeed.x = -SPEED_X;
//	}
//}