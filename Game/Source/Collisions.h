#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

#include "Module.h"
#include "SDL/include/SDL.h"

struct Collider
{
	enum Type
	{
		NONE = 0,
		PLAYER,
		BLOCK,
		LAVA,

		MAX
	};
	//Variables
	SDL_Rect rect;						// Box of the collider
	bool pendingToDelete = false;		// Deletes collider if its true
	Collider::Type type;							
	Module* listener = nullptr;

	//Methods
	Collider(SDL_Rect rectangle, Collider::Type type, Module* listener = nullptr) : rect(rectangle), type(type), listener(listener) {}
	Collider() {};

	inline void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	inline bool Intersects(const SDL_Rect& r) const;
};

class Collisions : public Module
{
public:
	Collisions();

	bool Init();

	virtual ~Collisions() {};
	
	bool Awake(pugi::xml_node& node);

	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, Collider::Type type, Module* listener);

private:
	void DebugDraw(); 

public:
	List<Collider*> colliders;
	bool debug;
};

#endif // !__COLLISIONS_H__


