#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Point.h"
#include "Animation.h"
#include "ModuleEntities.h"

struct SDL_Texture;
struct Collider;

class Entity
{
public:

	enum DirectionState { LEFT, RIGHT, UP, DOWN, IDLE };
	// Constructor
	// Saves the spawn position for later movement calculations
	Entity(int x, int y);

	// Destructor
	virtual ~Entity();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update(float dt);

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(Collider* collider);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

public:
	// The current position in the world
	iPoint position;

	// The enemy's collider
	Collider* collider = nullptr;

	// The enemy's texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* debugTexture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;
	SString name = SString("NONE");
	
	bool isDead = false;

	EntityType entityType;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;

	iPoint entitySpeed = { 0,0 };

	DirectionState direction = IDLE;
	float counter = 0;
	bool inCollision = false;

	bool goingLeft = true;

	bool climbingUP = false;

	bool climbingDOWN = false;


	int tempx = 0;
};

#endif // __ENEMY_H__