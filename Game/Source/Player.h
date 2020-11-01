#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__


#include "Module.h"
#include "Point.h"
#include "Animation.h"

#define PIXELS_PER_METER 50.0f
#define METER_PER_PIXEL 0.02f

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p) ((float) METER_PER_PIXEL * p)

struct SDL_Texture;
struct Collider;
struct Animation;

class Player : public Module
{
public:
	Player();

	~Player();

	bool Init();

	bool Start();
	
	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	bool OnCollision(Collider* c1, Collider* c2);

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&)const;

	void Logic(float dt);



public:
	iPoint playerPos;
	iPoint velocity = { 0 , 0 };
	Collider* playerCollider = nullptr;
	Collider* collider = nullptr;
	iPoint position;

	Animation* currentAnim = nullptr;
	Animation idleLeftAnim;
	Animation idleRightAnim;
	Animation runLeftAnim;
	Animation runRightAnim;
	Animation attackLeftAnim;
	Animation attackRightAnim;
	Animation dieLeftAnim;
	Animation dieRightAnim;
	Animation jumpLeftAnim;
	Animation jumpRightAnim;
	Animation fallLeftAnim;
	Animation fallRightAnim;

	SDL_Texture** currentTexture = nullptr;
	SDL_Texture* texture = nullptr;

	bool destroyed = false;
	bool collisionExist = false;
	bool door = false;


private:
	
	void Input();

	bool isGround = false;
	bool isAir = true;
	bool isJumping = false;
	bool isGoingRight = false;
	bool collisionFromBelow = false;
	bool isDead = false;
	bool godMode = false;

};

#endif
