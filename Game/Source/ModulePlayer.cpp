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

	// left idle animation
	/*leftIdleAnim.PushBack({ 66, 24, 12, 16 });
	leftIdleAnim.loop = true;
	leftIdleAnim.speed = 0.1f;*/

	//// right idle animation
	//idleAnim.PushBack({ 0, 298, 66, 80 });
	//idleAnim.loop = true;
	//idleAnim.speed = 0.1f;

	//rightRunAnim.PushBack({ 0, 0, 66, 79 });
	//rightRunAnim.PushBack({ 73, 0, 66, 78 });
	//rightRunAnim.PushBack({ 145, 0, 66, 75 });
	//rightRunAnim.PushBack({ 219, 0, 94, 59 });
	//rightRunAnim.PushBack({ 319, 0, 73, 66 });
	//rightRunAnim.loop = true;
	//rightRunAnim.speed = 0.15f;

	//leftRunAnim.PushBack({ 327, 96, 66, 79 }); // movement left 1
	//leftRunAnim.PushBack({ 255, 96, 66, 78 }); // idle left
	//leftRunAnim.PushBack({ 181, 96, 66, 75 }); // movement left 2
	//leftRunAnim.PushBack({ 79, 96, 94, 59 }); // idle left
	//leftRunAnim.PushBack({ 0, 96, 73, 66 });
	//leftRunAnim.loop = true;
	//leftRunAnim.speed = 0.15f;

	//jumpAnim.PushBack({ 0, 298, 66, 80 });
	//jumpAnim.PushBack({ 81, 300, 67, 74 });
	//jumpAnim.PushBack({ 165, 310, 64, 56 });
	//jumpAnim.loop = false;
	//jumpAnim.pingpong = false;
	//jumpAnim.speed = 0.15f;

	//dieAnimation.PushBack({ 264, 205, 63, 66 });
	//dieAnimation.loop = false;
	//dieAnimation.speed = 0.15f;

	//fallAnim.PushBack({ 0,188,66,79 });
	//fallAnim.loop = false;
	//fallAnim.speed = 0.15f;

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
	jumpTexture = app->tex->Load("Assets/textures/spritesheet.png");
	dieTexture = app->tex->Load("Assets/textures/spritesheet.png");
	fallTexture = app->tex->Load("Assets/textures/spritesheet.png");

	// Audio of the player's actions

	walkingSfx = app->audio->LoadFx("Assets/Audio/Fx/player_walking.wav");
	jumpingSfx = app->audio->LoadFx("Assets/Audio/Fx/player_jump.wav");
	shootingSfx = app->audio->LoadFx("Assets/Audio/Fx/player_shot.wav");

	//Starting position of the player
	playerWh = { 66.0f,79.0f };
	// playerCollider = app->collisions->AddCollider({(int)playerPos.x + (int)playerWh.x / 2,(int)playerPos.y,(int)playerWh.x/2,(int)playerWh.y}, Collider::Type::PLAYER, (Module*)app->player);
	playerCollider = app->collisions->AddCollider({ (int)playerPos.x +2,(int)playerPos.y,12,16 }, Collider::Type::PLAYER, (Module*)app->player);
	

	currentAnimation = &idleRightAnim;
	currentTexture = &texture;

	playerState = ON_AIR;
	collisionExist = false;
	collisionFromBelow = false;
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

	if (velocity.y>=250.f/*dt*1000.0f > app->cappedMs*/)
	{
		float newDt = dt/25.0f;
		for (int i = 0; i < 5; ++i)
		{
			Logic(newDt);
			CheckCollisions(newDt);
		}
		LOG("---------SUBSTEPPING---------");
	}

	if (currentAnimation != NULL)
	{
		currentAnimation->Update();
	}

	return ret;
}

void ModulePlayer::Input(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !godMode)
	{
		// Controlling player movement based on if they are on the ground or air.
		

		if (currentAnimation != &runLeftAnim)
		{
			runLeftAnim.Reset();
			currentAnimation = &runLeftAnim;
		}
		if (playerState == ON_GROUND)
		{
			velocity.x += -VELOCITY * 1.5f * dt;
			if (isWalking == false) 
				isWalking = app->audio->PlayFx(walkingSfx);
			if (counterWalking.Read() >= 20.0f)
			{
				isWalking = false;
			}
			counterWalking.Start();
		}
		else
		{
			velocity.x += -VELOCITY * 1.2f * dt;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP && isJump == false && !godMode)
	{
		velocity.x = 0;
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && godMode)
	{
		velocity.x = -VELOCITY;
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP && godMode)
	{
		velocity.x = 0;
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !godMode)
	{
		// Controlling player movement based on if they are on the ground or air.
		//velocity.x += (isGround ? VELOCITY : VELOCITY) * dt;
		

		if (currentAnimation != &runRightAnim)
		{
			runRightAnim.Reset();
			currentAnimation = &runRightAnim;
		}
		if (playerState == ON_GROUND)
		{
			velocity.x += VELOCITY * 1.5f * dt;
			if (isWalking == false)
				isWalking = app->audio->PlayFx(walkingSfx);
			if (counterWalking.Read() >= 20.0f)
			{
				isWalking = false;
			}
			counterWalking.Start();
		}
		else
		{
			velocity.x += VELOCITY * 1.2f * dt;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP && isJump == false && !godMode)
	{
		velocity.x = 0;
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP && godMode)
	{
		velocity.x = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && godMode)
	{
		velocity.x = VELOCITY;
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && godMode)
	{
		velocity.y = VELOCITY;
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_UP && godMode)
	{
		velocity.y = 0;
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && godMode)
	{
		velocity.y = -VELOCITY;
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP && godMode)
	{
		velocity.y = 0;
	}
	


	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && playerState == ON_GROUND)
	{
		// Stop moving just before jumping
		velocity.x = velocity.x / 2;
		if (velocity.y == 0)
		{
			velocity.y = -85.0f * 2;
			playerState = ON_AIR;
			isJump = true;
			app->audio->PlayFx(jumpingSfx);
		}
	/*	velocity.y = -160.0f * 2;
		isAir = true;*/
		if (velocity.x > 0)
			jumpRightAnim.Reset();
		else if (velocity.x < 0)
			jumpLeftAnim.Reset();
	}

	// If last movement was left, set the current animation back to left idle
	if (app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_UP)
	{
		currentAnimation = &idleLeftAnim;
	}

	// If last movement was right, set the current animation back to left idle
	if (app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_UP)
	{
		currentAnimation = &idleRightAnim;
	}

	// Debug Keys
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		godMode = !godMode;
	}

	if (app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		destroyed = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_C) == KEY_REPEAT)
	{
		// Teleport Checkpoint
		Collider* dstCheckpoint = NULL;
		for (int i = 0; i < app->map->checkpointsList.Count(); ++i)
		{
			// SDL_SCANCODE_0 is 39 SDL_SCANCODE_1 is 30 SDL_SCANCODE_2 is 31
			if(app->input->GetKey(30+i) == KEY_DOWN)
			{
				dstCheckpoint = app->map->checkpointsList.At(i)->data;
				break;
			}
		}

		if (dstCheckpoint != NULL)
		{
			playerPos = { (float)dstCheckpoint->rect.x,(float)dstCheckpoint->rect.y };
			velocity = { 0.0f,0.0f };
		}
	}

	BulletLogic(dt);
}

void ModulePlayer::BulletLogic(float dt)
{
	iPoint mousePoint;
	app->input->GetMousePosition(mousePoint.x, mousePoint.y);

	uPoint window;
	app->win->GetWindowSize(window.x, window.y);

	fPoint center = { (float)window.x / 2,(float)window.y / 2 };

	fPoint direction;
	direction = { center.x - mousePoint.x , center.y - mousePoint.y };

	float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

	direction = { direction.x / magnitude, direction.y / magnitude }; // Vector unitario/dirección
	direction.Negate();

	/*printf("mouse = %f %f\n", center.x, center.y);
	printf("dir = %f %f\n", direction.x, direction.y);*/

	if ((app->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN))
	{
		Particle newBullet = app->particles->bullet;
	
		newBullet.speed.y = { direction.y * 500.0f +app->player->velocity.y};
		newBullet.speed.x = { direction.x * 500.0f + app->player->velocity.x};

		app->particles->AddParticle(newBullet, playerPos.x + playerWh.x/2, playerPos.y, Collider::Type::BULLET);
		app->audio->PlayFx(shootingSfx);
	}
}

void ModulePlayer::Logic(float dt)
{
	CheckPlayerState(dt);

	if (health == 0)
		destroyed = true;

	printf("Velocity in X = %f\nVelocity in Y = %f\n\n", velocity.x, velocity.y);
	/*printf("Position in X = %f\nPosition in Y = %f\n\n", playerPos.x, playerPos.y);*/

	// Integrators
	if (destroyed == false)
	{
		playerPos.x = playerPos.x + velocity.x * dt;
		playerPos.y = playerPos.y + velocity.y * dt;

		// Borders for the player
		if (playerPos.x < 0)
			playerPos.x = 0;
		if (playerPos.x + playerCollider->rect.w > 100 * 16)
			playerPos.x = 100 * 16 - playerCollider->rect.w;
		if (playerPos.y < 0)
			playerPos.y = 0;
		if (playerPos.y + playerCollider->rect.h > 50 * 16)
			playerPos.y = 50 * 16 - playerCollider->rect.y;

		playerCollider->SetPos(playerPos.x, playerPos.y);
	}

	// Limit max velocities
	if (velocity.x > MAXVELOCITY_X)
		velocity.x = MAXVELOCITY_X;
	if (velocity.x < -MAXVELOCITY_X)
		velocity.x = -MAXVELOCITY_X;

	if (velocity.y > MAXVELOCITY_Y)
		velocity.y = MAXVELOCITY_Y;
	if (velocity.y < -MAXVELOCITY_Y)
		velocity.y = -MAXVELOCITY_Y;

	/*printf("Ground = %s\n", isGround ? "true" : "false");
	printf("Air = %s\n", isAir ? "true" : "false");*/
	/*printf("Jump = %s\n", isJump ? "true" : "false");*/
}

void ModulePlayer::CheckPlayerState(float dt)
{
	// Gravity
	if ((playerState == ON_AIR || collisionExist == false) && godMode == false && destroyed == false)
	{
		if (collisionExist == false)
			playerState = ON_AIR;

		currentTexture = &jumpTexture;
		/*currentAnimation = &jumpRightAnim;*/

		if (velocity.y <= -200)
		{
			//velocity.y += 100.0f/2 * dt;
			velocity.y += 100.0f * 4.0f * dt;
		}
		else
		{
			velocity.y += 100.0f * 3.0f * dt;
		}

		if (velocity.y < 0)
		{
			playerDirection = UP;
			if (velocity.x > 0)
				currentAnimation = &jumpRightAnim;
			else if (velocity.x < 0)
				currentAnimation = &jumpLeftAnim;
		}
		else if (velocity.y >= 0)
		{
			playerDirection = DOWN;
			if (velocity.x > 0)
				currentAnimation = &fallRightAnim;
			else if (velocity.x < 0)
				currentAnimation = &fallLeftAnim;
		}

		if (velocity.x) // Make player lose some velocity in x while is in air
		{
			velocity.x += -0.9f * velocity.x * dt; // Resistence/Friction in the air
		}
	}

	if (playerState == ON_GROUND) // Stopping the player gradually while at ground
	{
		currentTexture = &texture;
		if (currentAnimation == &jumpLeftAnim)
		{
			velocity.x = 0;
			currentAnimation = &idleLeftAnim;
		}
		else if (currentAnimation == &jumpRightAnim)
		{
			velocity.x = 0;
			currentAnimation = &idleRightAnim;
		}
		if (playerState != ON_AIR && godMode == false)
		{
			velocity.y = 0;
		}
		velocity.x += -3.2f * velocity.x * dt; // Resistence/Friction in the ground
		if (fabs(velocity.x) < 0.5f) // Stop the player once velocity is too small
			velocity.x = 0;
	}

	if (destroyed)
	{
		if (velocity.x > 0)
			currentAnimation = &dieRightAnim;
		if (velocity.x < 0)
			currentAnimation = &dieLeftAnim;
		currentTexture = &dieTexture;
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
	//
	ListItem<Collider*>* listColliders;
	
	for (listColliders = app->collisions->colliders.start; listColliders != NULL; listColliders = listColliders->next)
	{
		if (playerCollider->Intersects(listColliders->data->rect))
		{
			collisionExist = this->OnCollision(playerCollider, listColliders->data);
			if (listColliders->data->listener != nullptr && listColliders->data->type != Collider::Type::PLAYER)
			{
				if(listColliders->data->type != Collider::Type::BULLET)
					listColliders->data->listener->OnCollision(listColliders->data, playerCollider);
			}
		}
	}

	return ret;
}

bool ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	bool ret = false;

	if (c2->type == Collider::Type::GROUND)
	{
		//If player head enters the ground first collisionFromBelow = true
		//If collider of the ground is between the top of the head and the waist
		if (((playerCollider->rect.y < c2->rect.y) || (playerCollider->rect.y > c2->rect.y)) && (playerCollider->rect.y + playerCollider->rect.h > c2->rect.y +c2->rect.h/2))
		{
			collisionFromBelow = true;
			LOG("Player through the ground");
			ret = false;
		}
		else
			collisionFromBelow = false;

		if (collisionFromBelow == false)
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
				LOG("Player feet on ground");
				ret = true;
			}
		}

		previousCollision = c2;
	}
	
	if (c2->type == Collider::Type::CHECKPOINT && previousCollision->type != Collider::Type::CHECKPOINT)
	{
		LOG("SAVING GAME");
		app->SaveGameRequest();
		previousCollision = c2;
	}

	if (c2->type == Collider::Type::DEATH && previousCollision->type != Collider::Type::DEATH && godMode == false)
	{
		destroyed = true;
		previousCollision = c2;
	}

	if (c2->type == Collider::Type::ENEMY_HITBOX && previousCollision->type != Collider::Type::ENEMY_HITBOX && godMode == false)
	{
		health -= 1;
		previousCollision = c2;
	}

	if (c2->type == Collider::Type::ITEM && previousCollision->type != Collider::Type::ITEM && godMode == false)
	{

		switch (c2->item)
		{
		case Collider::Items::HEALTH:
			health += 1;
			previousCollision = c2;
			c2->listener->OnCollision(c2, c1);
			break;
		case Collider::Items::STAR:
			stars += 1;
			previousCollision = c2;
			c2->listener->OnCollision(c2, c1);
			break;
		default:
			break;
		}

		
	}

	if (c2->type == Collider::Type::WIN)
		win = true;

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

void ModulePlayer::PlayerDied()
{
	app->LoadGameRequest();
	app->player->destroyed = false;
	app->player->velocity.y = 0;
	app->player->velocity.x = 0;
	lives = lives - 1;
	health = 3;
}


bool ModulePlayer::CleanUp()
{
	//activeTextures = activeColliders = activeFonts = activeFx = 0;

	// TODO 1: Remove ALL remaining resources. Update resource count properly

	app->tex->UnLoad(texture);
	app->tex->UnLoad(jumpTexture);
	
	return true;
}