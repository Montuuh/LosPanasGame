#include "ModulePlayer.h"

#include "App.h"
#include "Audio.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "ModuleCollisions.h"
#include "Audio.h"
#include "ModuleFadeToBlack.h"
//#include "ModuleHud.h"
#include "DeathScene.h"
#include "ModuleParticles.h"
#include "Window.h"
#include "Map.h"

#include "Log.h"

#include <stdio.h>
#include "SDL/include/SDL_scancode.h"


//Now temporally is this
#define VELOCITY 200.0f
#define MAXVELOCITY_X 300.0f
#define MAXVELOCITY_Y 300.0f // Before it was 1000.0f

ModulePlayer::ModulePlayer(bool b) : Module(b)
{
	name.Create("player");

	// Left Idle Animation
	idleLeftAnim.PushBack({ 0, 0, 16, 16 });
	idleLeftAnim.PushBack({ 32, 0, 16, 16 });
	idleLeftAnim.PushBack({ 64, 0, 16, 16 });
	idleLeftAnim.PushBack({ 96, 0, 16, 16 });
	idleLeftAnim.loop = true;
	idleLeftAnim.speed = 0.1f;

	// Right Idle Animation
	idleRightAnim.PushBack({ 16, 0, 16, 16 });
	idleRightAnim.PushBack({ 48, 0, 16, 16 });
	idleRightAnim.PushBack({ 80, 0, 16, 16 });
	idleRightAnim.PushBack({ 112, 0, 16, 16 });
	idleRightAnim.loop = true;
	idleRightAnim.speed = 0.1f;

	// Left Run Animation
	runLeftAnim.PushBack({ 0, 16, 16, 16 });
	runLeftAnim.PushBack({ 32, 16, 16, 16 });
	runLeftAnim.PushBack({ 64, 16, 16, 16 });
	runLeftAnim.PushBack({ 96, 16, 16, 16 });
	runLeftAnim.loop = true;
	runLeftAnim.speed = 0.1f;

	// Right Run Animation
	runRightAnim.PushBack({ 16, 16, 16, 16 });
	runRightAnim.PushBack({ 48, 16, 16, 16 });
	runRightAnim.PushBack({ 80, 16, 16, 16 });
	runRightAnim.PushBack({ 112, 16, 16, 16 });
	runRightAnim.loop = true;
	runRightAnim.speed = 0.1f;

	// Left Attack Animation
	attackLeftAnim.PushBack({ 0, 32, 16, 16 });
	attackLeftAnim.PushBack({ 32, 32, 16, 16 });
	attackLeftAnim.PushBack({ 64, 32, 16, 16 });
	attackLeftAnim.PushBack({ 96, 32, 16, 16 });
	attackLeftAnim.PushBack({ 0, 48, 16, 16 });
	attackLeftAnim.PushBack({ 32, 48, 16, 16 });
	attackLeftAnim.PushBack({ 64, 48, 16, 16 });
	attackLeftAnim.PushBack({ 96, 48, 16, 16 });
	attackLeftAnim.loop = true;
	attackLeftAnim.speed = 0.1f;

	// Right Attack Animation
	attackRightAnim.PushBack({ 16, 32, 16, 16 });
	attackRightAnim.PushBack({ 48, 32, 16, 16 });
	attackRightAnim.PushBack({ 80, 32, 16, 16 });
	attackRightAnim.PushBack({ 112, 32, 16, 16 });
	attackRightAnim.PushBack({ 16, 48, 16, 16 });
	attackRightAnim.PushBack({ 48, 48, 16, 16 });
	attackRightAnim.PushBack({ 80, 48, 16, 16 });
	attackRightAnim.PushBack({ 112, 48, 16, 16 });
	attackRightAnim.loop = true;
	attackRightAnim.speed = 0.1f;

	// Left Die Animation
	dieLeftAnim.PushBack({ 0, 64, 16, 16 });
	dieLeftAnim.PushBack({ 32, 64, 16, 16 });
	dieLeftAnim.PushBack({ 64, 64, 16, 16 });
	dieLeftAnim.PushBack({ 96, 64, 16, 16 });
	dieLeftAnim.loop = false;
	dieLeftAnim.speed = 0.1f;

	// Right Die Animation
	dieRightAnim.PushBack({ 16, 64, 16, 16 });
	dieRightAnim.PushBack({ 48, 64, 16, 16 });
	dieRightAnim.PushBack({ 80, 64, 16, 16 });
	dieRightAnim.PushBack({ 112, 64, 16, 16 });
	dieRightAnim.loop = false;
	dieRightAnim.speed = 0.1f;

	// Left Jump Animation
	jumpLeftAnim.PushBack({ 0, 80, 16, 16 });
	jumpLeftAnim.PushBack({ 32, 80, 16, 16 });
	jumpLeftAnim.PushBack({ 64, 80, 16, 16 });
	jumpLeftAnim.PushBack({ 96, 80, 16, 16 });
	jumpLeftAnim.loop = true;
	jumpLeftAnim.speed = 0.1f;

	// Right Jump Animation
	jumpRightAnim.PushBack({ 16, 80, 16, 16 });
	jumpRightAnim.PushBack({ 48, 80, 16, 16 });
	jumpRightAnim.PushBack({ 80, 80, 16, 16 });
	jumpRightAnim.PushBack({ 112, 80, 16, 16 });
	jumpRightAnim.loop = true;
	jumpRightAnim.speed = 0.1f;

	// Left Fall Animation
	fallLeftAnim.PushBack({ 0, 96, 16, 16 });
	fallLeftAnim.PushBack({ 32, 96, 16, 16 });
	fallLeftAnim.PushBack({ 64, 96, 16, 16 });
	fallLeftAnim.PushBack({ 96, 96, 16, 16 });
	fallLeftAnim.loop = true;
	fallLeftAnim.speed = 0.1f;

	// Right Fall Animation
	fallRightAnim.PushBack({ 16, 96, 16, 16 });
	fallRightAnim.PushBack({ 48, 96, 16, 16 });
	fallRightAnim.PushBack({ 80, 96, 16, 16 });
	fallRightAnim.PushBack({ 112, 96, 16, 16 });
	fallRightAnim.loop = true;
	fallRightAnim.speed = 0.1f;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = app->tex->Load("Assets/textures/spritesheet.png"); 

	// Starting position of the player
	playerPos = { 66.0f,78.0f };
	
	// Setting starting position of the player's collider
	playerCollider = app->collisions->AddCollider({ (int)playerPos.x +2,(int)playerPos.y,12,16 }, Collider::Type::PLAYER, (Module*)app->player);
	
	// Loading starting animation && texture
	currentAnimation = &idleRightAnim;
	currentTexture = &texture;

	playerState = ON_AIR;

	godMode = false;

	isWalking = false;

	return ret;
}

bool ModulePlayer::Update(float dt)
{
	bool ret = true;

	if (dt > 1.0f / 30.0f)
	{
		dt = 1.0f / 30.0f;
	}

	Input(dt);

	Logic(dt);
	CheckCollisions(dt);

	if (currentAnimation != NULL)
	{
		currentAnimation->Update();
	}

	return ret;
}

void ModulePlayer::Input(float dt)
{

	// Player movement when going to the left
	if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (!godMode) && (!destroyed))
	{
		goingLeft = true;
		if (currentAnimation != &runLeftAnim)
		{
			runLeftAnim.Reset();
			currentAnimation = &runLeftAnim;
		}
		if (playerState == ON_GROUND)                   // If player moves to the right when in ground
			velocity.x += -VELOCITY * 1.2f * dt;
		else                                            // If player moves to the right when in air
			velocity.x += -VELOCITY * 0.5f * dt;
	}

	// Stop left movement when player stop pressing to the left
	if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_UP) && (playerState == ON_GROUND) && (!godMode) && (!destroyed))
	{
		goingLeft = false;
		velocity.x = 0;
		currentAnimation = &idleLeftAnim;
	}

	// God Mode movement 
	if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (godMode))
	{
		goingLeft = true;
		if (currentAnimation != &runLeftAnim)
		{
			runLeftAnim.Reset();
			currentAnimation = &runLeftAnim;
		}
		velocity.x = -VELOCITY / 2;
	}
	if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_UP) && (godMode))
	{
		goingLeft = false;
		velocity.x = 0;
		currentAnimation = &idleLeftAnim;
	}

	// Player movement when going to the right
	if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (!godMode) && (!destroyed))
	{
		goingRight = true;
		if (currentAnimation != &runRightAnim)
		{
			runRightAnim.Reset();
			currentAnimation = &runRightAnim;
		}
		if (playerState == ON_GROUND)                   // If player moves to the right when in ground
			velocity.x += VELOCITY * 1.2f * dt;
		else                                            // If player moves to the right when in air
			velocity.x += VELOCITY * 0.5f * dt;
	}

	// Stop left movement when player stop pressing to the right
	if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_UP) && (playerState == ON_GROUND) && (!godMode) && (!destroyed))
	{
		goingRight = false;
		velocity.x = 0;
		currentAnimation = &idleRightAnim;
	}

	// God Mode movement 
	if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (godMode))
	{
		goingRight = true;
		if (currentAnimation != &runRightAnim)
		{
			runRightAnim.Reset();
			currentAnimation = &runRightAnim;
		}
		velocity.x = VELOCITY / 2;
	}
	if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_UP) && (godMode))
	{
		goingRight = false;
		velocity.x = 0;
		currentAnimation = &idleRightAnim;
	}
	
	// God Mode movement up && down
	if ((app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (godMode))
	{
		velocity.y = VELOCITY / 2;
	}
	if ((app->input->GetKey(SDL_SCANCODE_S) == KEY_UP) && (godMode))
	{
		velocity.y = 0;
	}
	if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) && (godMode))
	{
		velocity.y = -VELOCITY / 2;
	}
	if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_UP) && (godMode))
	{
		velocity.y = 0;
	}
	

	// If player wants to jump && its on ground
	if ((app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && (playerState == ON_GROUND))
	{
		velocity.x = velocity.x / 2;
		if (velocity.y == 0)
		{
			velocity.y = -80.0f * 2;
			playerState = ON_AIR;
			isJump = true;
		}

		if (velocity.x > 0)
			jumpRightAnim.Reset();
		else if (velocity.x < 0)
			jumpLeftAnim.Reset();
	}

	// Debug Keys
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		godMode = !godMode;
	}

	if (app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		lives = 0;
	}
}

void ModulePlayer::Logic(float dt)
{
	CheckPlayerState(dt);

	if (lives == 0)
		destroyed = true;

	// Borders for the player
	if (playerPos.x < 0)
		playerPos.x = 0;
	if (playerPos.x + playerCollider->rect.w > 100 * 16)
		playerPos.x = 100 * 16 - playerCollider->rect.w;
	if (playerPos.y < 0)
		playerPos.y = 0;
	if (playerPos.y + playerCollider->rect.h > 50 * 16)
		playerPos.y = 50 * 16 - playerCollider->rect.y;

	// If player is alive, position and collider setters
	if (destroyed == false) 
	{
		playerPos.x = playerPos.x + velocity.x * dt;
		playerPos.y = playerPos.y + velocity.y * dt;

		playerCollider->SetPos(playerPos.x, playerPos.y);
	}

	// Limit high velocities
	if (velocity.x > MAXVELOCITY_X)
		velocity.x = MAXVELOCITY_X;
	if (velocity.x < -MAXVELOCITY_X)
		velocity.x = -MAXVELOCITY_X;

	if (velocity.y > MAXVELOCITY_Y)
		velocity.y = MAXVELOCITY_Y;
	if (velocity.y < -MAXVELOCITY_Y)
		velocity.y = -MAXVELOCITY_Y;
}

void ModulePlayer::CheckPlayerState(float dt)
{
	// Up & Down logics 
	if (((playerState == ON_AIR) || (collisionExist == false)) && (!godMode) && (!destroyed))
	{
		if (collisionExist == false)
			playerState = ON_AIR;

		// Gravity
		if (velocity.y <= -200)
		{
			velocity.y += 100.0f * 3.5f * dt;
		}
		else
		{
			velocity.y += 100.0f * 2.5f * dt;
		}

		// If player is going up (started jumping)
		if (velocity.y < 0)
		{
			playerDirection = UP;
			if (currentAnimation == &idleRightAnim || currentAnimation == &fallRightAnim || currentAnimation == &jumpRightAnim || currentAnimation == &attackRightAnim || currentAnimation == &runRightAnim)
				currentAnimation = &jumpRightAnim;
			if (currentAnimation == &idleLeftAnim || currentAnimation == &fallLeftAnim || currentAnimation == &jumpLeftAnim || currentAnimation == &attackLeftAnim || currentAnimation == &runLeftAnim)
				currentAnimation = &jumpLeftAnim;
		}

		// If player is going down (falling)
		if (velocity.y > 0)
		{
			playerDirection = DOWN;
			if (currentAnimation == &idleRightAnim || currentAnimation == &fallRightAnim || currentAnimation == &jumpRightAnim || currentAnimation == &attackRightAnim || currentAnimation == &runRightAnim)
				currentAnimation = &fallRightAnim;
			if (currentAnimation == &idleLeftAnim || currentAnimation == &fallLeftAnim || currentAnimation == &jumpLeftAnim || currentAnimation == &attackLeftAnim || currentAnimation == &runLeftAnim)
				currentAnimation = &fallLeftAnim;
		}
		
		// Making the jump and falling velocity in x more realistic
		velocity.x += -1.5f * velocity.x * dt;
	}

	// Ground movement logics
	if ((playerState == ON_GROUND) && (!godMode)) 
	{
		velocity.y = 0;

		// Making the movement more realistic, adding few frictions
		velocity.x += -2.75f * velocity.x * dt; 
		
		// Make the player to stop moving if the velocity is too small
		if (fabs(velocity.x) < 0.25f) 
			velocity.x = 0;

		// Make the player go to idle when the player touches the ground from falling
		if (currentAnimation == &fallRightAnim)
			currentAnimation = &idleRightAnim;
		if (currentAnimation == &fallLeftAnim)
			currentAnimation == &idleLeftAnim;
	}

	// Die animations && fade to death scene
	if (destroyed)
	{
		if (currentAnimation == &idleRightAnim || currentAnimation == &fallRightAnim || currentAnimation == &jumpRightAnim || currentAnimation == &attackRightAnim || currentAnimation == &runRightAnim)
			currentAnimation = &dieRightAnim;
		if (currentAnimation == &idleLeftAnim || currentAnimation == &fallLeftAnim || currentAnimation == &jumpLeftAnim || currentAnimation == &attackLeftAnim || currentAnimation == &runLeftAnim)
			currentAnimation = &dieLeftAnim;
	}
}


bool ModulePlayer::PostUpdate()
{
	bool ret = true;

	if (currentAnimation != NULL)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		app->render->DrawTexture(*currentTexture, playerPos.x, playerPos.y, &rect);
	}

	return ret;
}

bool ModulePlayer::CheckCollisions(float dt)
{
	bool ret = true;
	collisionExist = false;
	//Check manually all collisions with player
	
	ListItem<Collider*>* L;
	
	for (L = app->collisions->colliders.start; L != NULL; L = L->next)
	{
		if (playerCollider->Intersects(L->data->rect))
		{
			collisionExist = this->OnCollision(playerCollider, L->data);
			if (L->data->listener != nullptr && L->data->type != Collider::Type::PLAYER)
			{
					L->data->listener->OnCollision(L->data, playerCollider);
			}
		}
	}

	return ret;
}

bool ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	bool ret = false;

	if (c2->type == Collider::Type::GROUND && !godMode)
	{
		//If player head enters the ground first collisionFromBelow = true
		//If collider of the ground is between the top of the head and the waist
		if (((playerCollider->rect.y < c2->rect.y) || (playerCollider->rect.y > c2->rect.y)) && (playerCollider->rect.y + playerCollider->rect.h > c2->rect.y +c2->rect.h/2))
		{
			colliderAbove = true;
			ret = false;
			playerPos.y = c2->rect.y + c2->rect.h + 1;
			velocity.y = 10;
		}
		else
			colliderAbove = false;

		if (colliderAbove == false)
		{
			// Maintain the feet to the ground
			if ((playerCollider->rect.y + playerCollider->rect.h >= c2->rect.y) && (playerCollider->rect.y + playerCollider->rect.h <= c2->rect.y + c2->rect.h/2))
			{
				if (!(playerCollider->rect.y + playerCollider->rect.h <= c2->rect.y + 4))
					playerPos.y += -0.5f;
				else
					playerPos.y = c2->rect.y - playerCollider->rect.h;
				/*isGround = true;*/
				//playerState = ON_GROUND;
				if (playerState == ON_AIR)
				{
					//isAir = false;
					if (velocity.x > 0)
						currentAnimation = &idleRightAnim;
					else if (velocity.x < 0)
						currentAnimation = &idleLeftAnim;
				}
				playerState = ON_GROUND;
				isJump = false;
				ret = true;
			}
			else if (goingRight)
			{
				if (playerCollider->rect.x + playerCollider->rect.w > c2->rect.x)
				{
					playerPos.x = c2->rect.x - playerCollider->rect.w - 1;
				}
			}
			else if (goingLeft)
			{
				if (playerCollider->rect.x < c2->rect.x + c2->rect.w)
				{
					playerPos.x = c2->rect.x + c2->rect.w;
				}
			}
		}

		previousCollision = c2;
	}
	
	if (c2->type == Collider::Type::CHECKPOINT && (previousCollision->type != Collider::Type::CHECKPOINT))
	{
		app->SaveGameRequest();
		previousCollision = c2;
	}

	if (c2->type == Collider::Type::DEATH && (previousCollision->type != Collider::Type::DEATH) && !godMode)
	{
		LoseLife();
		previousCollision = c2;
	}

	if (c2->type == Collider::Type::ITEM && (previousCollision->type != Collider::Type::ITEM))
	{

		switch (c2->item)
		{
		case Collider::Items::HEALTH:
			lives += 1;
			previousCollision = c2;
			c2->listener->OnCollision(c2, c1);
			break;
		case Collider::Items::DIAMOND:
			diamonds += 1;
			previousCollision = c2;
			c2->listener->OnCollision(c2, c1);
			break;
		default:
			break;
		}

		
	}

	if (c2->type == Collider::Type::WIN && (previousCollision->type != Collider::Type::WIN))
	{
		if (playerCollider->rect.x / 2 == c2->rect.x / 2)
		{
			hasWon = true;
			previousCollision = c2;
		}
	}

	return ret;
}

bool ModulePlayer::LoadState(pugi::xml_node& data)
{
	//...
	LOG("Loading Player state...");
	playerPos.x = data.child("position").attribute("x").as_int();
	playerPos.y = data.child("position").attribute("y").as_int();
	LOG("Player state succesfully loaded.\n Pos.x = %d Pos.y = %d", playerPos.x, playerPos.y);
	return true;
}


bool ModulePlayer::SaveState(pugi::xml_node& data) const
{
	//...
	// Delete old data
	data.remove_child("position");
	// Add new data
	LOG("Saving Player state...");
	pugi::xml_node pos = data.append_child("position");
	pos.append_attribute("x").set_value(playerPos.x);
	pos.append_attribute("y").set_value(playerPos.y);
	LOG("Player state succesfully saved. \n Pos.x = %d Pos.y = %d", playerPos.x, playerPos.y);
	return true;
}

void ModulePlayer::LoseLife()
{
	lives = lives - 1;
	if (lives > 0)
	{
		app->player->velocity.x = 0;
		app->player->velocity.y = 0;
		app->LoadGameRequest();
	}
	else if (lives == 0)
	{
		app->player->destroyed = true;
	}
}


bool ModulePlayer::CleanUp()
{
	app->tex->UnLoad(texture);
	
	return true;
}