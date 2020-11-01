#include "App.h"
#include "Collisions.h"
#include "Map.h"
#include "Render.h"
#include "Input.h"
#include "Log.h"

Collisions::Collisions() : Module()
{
	name.Create("collisions");
}

bool Collisions::Init()
{
	return true;
}

bool Collisions::Awake(pugi::xml_node& configNode)
{
	return true;
}

bool Collisions::Start()
{
	debug = false;

	return true;
}

bool Collisions::PreUpdate()
{
	// Deletes colliders if pendingToDelete = true
	ListItem<Collider*>* colliderList;
	colliderList = colliders.start;
	while (colliderList != nullptr)
	{
		if (colliderList->data->pendingToDelete == true)
		{
			colliders.del(colliderList);
		}
		colliderList = colliderList->next;
	}

	// Collision calculation
	Collider* c1;
	Collider* c2;
	colliderList = colliders.start;
	while (colliderList != NULL)
	{
		c1 = colliderList->data;
		ListItem<Collider*>* secondColliderList;
		secondColliderList = colliders.start;
		while (secondColliderList != NULL)
		{
			c2 = secondColliderList->data;
			if (c1 != c2)
			{
				if (c1->Intersects(c2->rect) == true && (c1->type == Collider::Type::PLAYER || c2->type == Collider::Type::PLAYER))
				{
					//if (c1->listener) c1->listener->OnCollision(c1, c2);
					//if (c2->listener) c2->listener->OnCollision(c2, c1);
				}
			}
			secondColliderList = secondColliderList->next;
		}
		colliderList = colliderList->next;
	}
	return true;
}

bool Collisions::Update(float dt)
{
	DebugDraw();
	return true;
}

bool Collisions::PostUpdate()
{
	return true;
}

bool Collisions::CleanUp()
{
	return true;
}

void Collisions::DebugDraw()
{
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		if (debug)
			debug = !debug;
		else
			debug = true;
	}
	if (!debug)
		return;
	
	uint alpha = 60;
	ListItem<Collider*>* colliderList;
	colliderList = colliders.start;
	while (colliderList != NULL)
	{
		switch (colliderList->data->type)
		{
		case Collider::Type::PLAYER: // green
			app->render->DrawRectangle(colliderList->data->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::BLOCK: // blue
			app->render->DrawRectangle(colliderList->data->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::LAVA: // red
			app->render->DrawRectangle(colliderList->data->rect, 255, 0, 0, alpha);
			break;
		}
		colliderList = colliderList->next;
	}
}

Collider* Collisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = new Collider;

	ret->rect = rect;
	ret->type = type;
	ret->listener = listener;

	colliders.add(ret);

	return ret;
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	return 
		((r.x + r.w > rect.x) &&
		(r.x < rect.x + rect.w) &&
		(r.y + r.h > rect.y) &&
		(r.y < rect.y + rect.h));
}