#include "EntityManager.h"

#include "App.h"

#include "Render.h"
#include "Window.h"
#include "Textures.h"
#include "Audio.h"
#include "Log.h"
#include "List.h"
#include "ModuleCollisions.h"
#include "Entity.h"

#include "ItemHealth.h"
#include "ItemDiamond.h"


#define SPAWN_MARGIN 50
#define MAX_ENTITIES 20

Entities::Entities(bool startEnabled) : Module(startEnabled)
{
	name.Create("entity");
	
}

Entities::~Entities()
{

}

bool Entities::Start()
{

	texture = app->tex->Load("Assets/Maps/def_tileset.png");
	itemPickedFx = app->audio->LoadFx("Assets/Audio/Fx/item_taken.wav");


	return true;
}


bool Entities::PreUpdate()
{
	bool ret = true;

	ListItem<Entity*>* list;
	for (list = entities.start; list != NULL && list->data != nullptr; list = list->next)
	{
		if (list != NULL && list->data->pendingToDelete)
		{
			entities.Del(list);
		}
	}

	//ListItem<Entity*>* list;
	//list = entities.start;

	//for (int i = 0; i < entities.Count(); ++i)
	//{
	//	if (list != NULL && list->data->pendingToDelete)
	//	{
	//		/*delete newEntity;
	//		enemies[i] = nullptr;*/
	//		entities.Del(list);
	//	}
	//	list = list->next;
	//}

	return ret;
}

bool Entities::Update(float dt)
{
	bool ret = true;
	HandleEnemiesSpawn();

	//ListItem<Entity*>* list;
	//list = entities.start;

	//for (int i = 0; i < entities.Count(); ++i)
	//{
	//	if (list != NULL)
	//		list->data->Update(dt);
	//	list = list->next;
	//}
	ListItem<Entity*>* list;
	for (list = entities.start; list != NULL && list->data != nullptr; list = list->next)
	{
		list->data->Update(dt);
	}
	

	return ret;
}

bool Entities::PostUpdate()
{
	bool ret = true;

	//ListItem<Entity*>* list;
	//list = entities.start;

	//for (int i = 0; i < entities.Count(); ++i)
	//{
	//	if (list != NULL)
	//		list->data->Draw();
	//	list = list->next;
	//}

	ListItem<Entity*>* list;
	for (list = entities.start;  list != NULL && list->data != nullptr; list = list->next)
	{
		list->data->Draw();
	}


	return ret;
}

// Called before quitting
bool Entities::CleanUp()
{
	bool ret = true;
	//app->audio->UnloadFx(enemyDestroyedFx);
	//app->audio->UnloadFx(itemPickedFx);
	
	app->tex->UnLoad(texture);


	LOG("Freeing all enemies");

	ListItem<Entity*>* list;
	list = entities.start;
	for (int i = 0; i < entities.Count(); ++i)
	{
		if (list != NULL)
		{
			entities.Del(list);
		}
		list = list->next;
	}
	entities.Clear();

	return ret;
}

bool Entities::AddEntity(EntityType type, int x, int y)
{
	bool ret = true;

	EntitySpawnpoint spawn;
	spawn.type = type;
	spawn.x = x;
	spawn.y = y;

	spawnQueue.Add(spawn);

	return ret;
}

void Entities::HandleEnemiesSpawn()
{

	ListItem<EntitySpawnpoint>* list;
	list = spawnQueue.start;
	int count = spawnQueue.Count();

	for (int i = 0; i < count; ++i)
	{
		if (list->data.type != EntityType::NO_TYPE)
		{
			SpawnEnemy(list->data);
			list->data.type = EntityType::NO_TYPE; 
		}
		list = list->next;
	}
}

void Entities::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	//for (uint i = 0; i < MAX_ENEMIES; ++i)
	//{
	//	if (enemies[i] != nullptr)
	//	{
	//		// Delete the enemy when it has reached the end of the screen
	//		if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
	//		{
	//			LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

	//			enemies[i]->SetToDelete();
	//		}
	//	}
	//}

	ListItem<Entity*>* list;
	list = entities.start;
	for (int i = 0; i < entities.Count(); ++i)
	{
		if (list != NULL)
		{
			if (list->data->position.x * app->win->GetScale() < (app->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", list->data->position.x * app->win->GetScale());

				list->data->SetToDelete();
			}
		}
		list = list->next;
	}
}

void Entities::SpawnEnemy(const EntitySpawnpoint& info)
{
	Entity* newEntity = NULL;
	switch (info.type)
	{
	case EntityType::ITEM_HEALTH:
	{
		newEntity = new ItemHealth(info.x, info.y);
		newEntity->texture = texture;

		break;
	}
	case EntityType::ITEM_DIAMOND:
	{
		newEntity = new ItemDiamond(info.x, info.y);
		newEntity->texture = texture;

		break;
	}

	}
	entities.Add(newEntity);
}

bool Entities::OnCollision(Collider* c1, Collider* c2) // This is called through listener from the OnCollision(c2,c1) of player.cpp c2->entity rect c1->player rect
{
	ListItem<Entity*>* entitiesList;
	entitiesList = entities.start;
	for (int i = 0; i < entities.Count(); ++i)
	{
		entitiesList = entities.At(i);
		if (entitiesList->data->GetCollider() == c1)
			entitiesList->data->OnCollision(c2);
	}
	
	/*for (int i = 0; i < ent.Count(); ++i)
	{
		for (ListItem<Collider*>*collsList = app->collisions->colliders.start; collsList != NULL ; collsList = collsList->next)
		{
			if (entitiesList->data->GetCollider()->Intersects(collsList->data->rect))
			{
				entitiesList->data->OnCollision(collsList->data);
			}
			collsList = collsList->next;
		}
		entitiesList = entitiesList->next;
	}*/
	
	return true;
}

bool Entities::SaveState(pugi::xml_node& data) const
{
	bool ret = true;

	pugi::xml_node entitiesCountNode;
	entitiesCountNode = data;
	entitiesCountNode.child("entitiesCount").attribute("Num").set_value(this->entities.Count());
	

	pugi::xml_node entitiesNode;
	entitiesNode = data.child("entitiesList");
	for (int i=0; i< MAX_ENTITIES;++i)
	{
		bool isRemoved = entitiesNode.remove_child("entities");
		if (isRemoved == false)
			break;
	}


	ListItem<Entity*>* L2;
	L2 = entities.start;
	for (int i = 0; i < this->entities.Count(); ++i)
	{
		L2->data = entities.At(i)->data;

		pugi::xml_node newEntitiesNode = data.child("entitiesList");
		newEntitiesNode = newEntitiesNode.append_child("entities");
		newEntitiesNode.append_attribute("id").set_value(i);
		newEntitiesNode.append_attribute("Type").set_value(L2->data->entityType);
		newEntitiesNode.append_attribute("Item").set_value(L2->data->GetCollider()->item);
		newEntitiesNode.append_attribute("x").set_value(L2->data->GetCollider()->rect.x);
		newEntitiesNode.append_attribute("y").set_value(L2->data->GetCollider()->rect.y);

	}
	return ret;
}

bool Entities::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	int count = entities.Count();
	for (int i = 0; i < count; i++)
	{
		entities.At(i)->data->SetToDelete();
	}
	entities.Clear();

	pugi::xml_node entitiesCountNode;
	entitiesCountNode = data.child("entitiesCount");
	int entitiesCount = entitiesCountNode.attribute("Num").as_int();

	pugi::xml_node entitiesListNode;
	entitiesListNode = data.child("entitiesList").child("entities");
	for (int i = 0; i < entitiesCount; i++)
	{
		int x = entitiesListNode.attribute("x").as_int();
		int y = entitiesListNode.attribute("y").as_int();
		int type = entitiesListNode.attribute("Type").as_int();
		int item = entitiesListNode.attribute("Item").as_int();

		EntityType val = static_cast<EntityType>(type);

		AddEntity(val, x, y);

		entitiesListNode = entitiesListNode.next_sibling();
	}


	return ret;
}