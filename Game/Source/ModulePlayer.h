#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Timer.h"

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)


struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool b);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start();

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	bool Update(float dt);

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	bool PostUpdate() ;
	
	bool CleanUp();

public:
	// Position of the player in the map
	fPoint playerPos;
	fPoint colliderPos;

	// The speed in which we move the player (pixels per frame)
	fPoint velocity = { 0,0 };

	Collider* playerCollider = nullptr;
	Collider* previousCollision = nullptr;

	Animation* currentAnimation = nullptr;
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

	// Collision callback, called when the player intersects with another collider
	bool OnCollision(Collider* c1, Collider* c2);

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	bool cameraFollow = false;
	bool collisionExist = false;
	bool destroyed = false;
	bool hasWon = false;
	bool hasLostLife = false;


private:
	enum PlayerState {ON_GROUND, ON_AIR};
	PlayerState playerState = ON_GROUND;
	enum PlayerDirection {RIGHT,LEFT,UP,DOWN};
	PlayerDirection playerDirection;

	bool isJump = false;
	bool colliderAbove = false;
	bool godMode = false;
	bool goingLeft = false;
	bool goingRight = false;
	
	void Input(float dt);
	void Logic(float dt);
	bool CheckCollisions(float dt);

	void CheckPlayerState(float dt);

public:
	void LoseLife(); // Player loses a life and returns to the last checkpoint/start

	uint lives;
	uint health;
	uint diamonds;

	int isWalking = false;
	Timer counterWalking;
};

#endif //!__MODULE_PLAYER_H__