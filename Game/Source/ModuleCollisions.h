#ifndef __MODULE_COLLISIONS_H__
#define __MODULE_COLLISIONS_H__

#include "Module.h"
#include "Collider.h"
#include "List.h"
class ModuleCollisions : public Module
{
public:
	// Constructor
	// Fills all collision matrix data
	ModuleCollisions(bool startEnabled);

	// Destructor
	~ModuleCollisions();

	// Called at the beginning of the application loop
	// Removes all colliders pending to delete
	// Checks for new collisions and calls its listeners
	bool PreUpdate();

	// Called at the middle of the application loop
	// Switches the debug mode on/off
	bool Update(float dt);

	// Called at the end of the application loop
	// Draw all colliders (if debug mode is enabled)
	bool PostUpdate();

	// Removes all existing colliders
	bool CleanUp();

	// Adds a new collider to the list
	Collider* AddCollider(SDL_Rect rect, Collider::Type type, Module* listener = nullptr, Collider::Items Item = Collider::Items::ITEM_NONE);

	void RemoveCollider(Collider* collider);

	// Draws all existing colliders with some transparency
	void DebugDraw();

	inline uint GetColliderCount() const { return colliders.Count(); };

	List<Collider*> colliders;

	bool debug = false;

private:
	// All existing colliders in the scene
	//Collider* colliders[MAX_COLLIDERS] = { nullptr };

	// The collision matrix. Defines the interaction for two collider types
	// If set two false, collider 1 will ignore collider 
	bool matrix[Collider::Type::MAX][Collider::Type::MAX];

	// The amount of colliders loaded into the array
	uint colliderCount = 0;

public:
	
};

#endif // __MODULE_COLLISIONS_H__