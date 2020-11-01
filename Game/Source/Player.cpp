#include "Player.h"

#include "App.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Audio.h"
#include "Log.h"
#include "Animation.h"

#include "SDL/include/SDL_scancode.h"

#define VELOCITY 20.0f
#define MAXVELOCITY_X 200.0f
#define MAXVELOCITY_Y 300.0f

Player::Player() : Module()
{
	name.Create("player");

	// Right Idle Animation
	rightIdleAnim.PushBack({ 0, 0, 17, 14 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = 0.1f;

	// Left Idle Animation
	leftIdleAnim.PushBack({ 17, 0, 17, 14 });
	leftIdleAnim.loop = true;
	leftIdleAnim.speed = 0.1f;

	// Right Run Animation
	rightRunAnim.PushBack({ 0, 0, 17, 16 });
	rightRunAnim.PushBack({ 0, 16, 17, 16 });
	rightRunAnim.PushBack({ 0, 32, 17, 16 });
	rightRunAnim.PushBack({ 0, 48, 17, 16 });
	rightRunAnim.loop = true;
	rightRunAnim.speed = 0.1f;

	// Left Run Animation
	leftRunAnim.PushBack({ 17, 0, 17, 16 });
	leftRunAnim.PushBack({ 17, 16, 17, 16 });
	leftRunAnim.PushBack({ 17, 32, 17, 16 });
	leftRunAnim.PushBack({ 17, 48, 17, 16 });
	leftRunAnim.loop = true;
	leftRunAnim.speed = 0.1f;
}

Player::~Player()
{

}


bool Player::Start()
{
	bool ret = true;

	LOG("Loading player textures...");
	idleTexture = app->tex->Load("Assets/textures/Characters/Main1/Idle.png");
	runTexture = app->tex->Load("Assets/textures/Characters/Main1/Run.png");

	/*
	HAY QUE IMPLEMENTAR Y MODIFICAR EL PSD DEL JUMP
	jumpTexture = app->tex->Load("Assets/textures/Characters/Main1/Jump.png");
	*/

	/*
	HAY QUE IMPLEMENTAR Y MODIFICAR EL PSD DEL DIE
	dieTexture = app->tex->Load("Assets/textures/Characters/Main1/Die.png");
	*/


	playerPos = { 32, 738 };

	playerCollider = app->collisions->AddCollider(SDL_Rect({ playerPos.x, playerPos.y, 16, 14 }), Collider::Type::PLAYER, this);

	currentAnim = &rightIdleAnim;
	currentTexture = &idleTexture;
	collisionExist = false;
	isGround = false;
	isAir = true;
	collisionFromBelow = false;
	godMode = true;

	return ret;
}

bool Player::Update(float dt)
{
	bool ret = true;

	Input();
	Logic(dt);

	if (currentAnim != NULL)
	{
		currentAnim->Update();
	}

	return ret;
}

void Player::Input()
{
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		// Controlling player movement based on if they are on the ground or air.
		velocity.x += -VELOCITY;

		if (currentAnim != &leftRunAnim)
		{
			leftRunAnim.Reset();
			currentAnim = &leftRunAnim;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		velocity.x += VELOCITY;

		if (currentAnim != &rightRunAnim)
		{
			rightRunAnim.Reset();
			currentAnim = &rightRunAnim;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		velocity.x -= VELOCITY;
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		velocity.x += VELOCITY;
	}



	// Idle animations
	if (app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_UP)
	{
		currentAnim = &leftIdleAnim;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_UP)
	{
		currentAnim = &rightIdleAnim;
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
}

void Player::Logic(float dt)
{
	// If player is in the air
	if ((isAir || collisionExist == false) && !godMode && !destroyed)
	{
		isGround = false;
		currentTexture = &jumpTexture;
		if (velocity.x >= 0)
			currentAnim = &jumpRightAnim;
		else currentAnim = &jumpLeftAnim;

		if (velocity.y <= -200)
			velocity.y += 100.0f * 4.0f * dt;
		else
			velocity.y += 100.0f * 3.0f * dt;

		velocity.x += -5.0f * velocity.x * dt;
	}

	// If player is in ground
	if (isGround)
	{
		if (currentAnim == &jumpRightAnim)
		{
			currentTexture = &idleTexture;
			currentAnim = &rightIdleAnim;
		}
		else if (currentAnim == &jumpLeftAnim)
		{
			currentTexture = &idleTexture;
			currentAnim = &leftIdleAnim;
		}
		if (isAir == false && godMode == false)
			velocity.y = 0;
		velocity.x += -1.0f * velocity.x * dt;
		if (fabs(velocity.x) < 0.01f)
			velocity.x = 0;
	}

	// Animation changed if player dies
	if (destroyed)
	{
		currentTexture = &dieTexture;
		currentAnim = &dieAnim;
	}

	// Setting collider position && player position
	playerPos.x = playerPos.x + velocity.x * dt;
	playerPos.y = playerPos.y + velocity.y * dt;

	playerCollider->SetPos(playerPos.x, playerPos.y);

	// Moving camera
	/*if (!destroyed)
	{
		app->render->camera.x = app->render->camera.w / 2 - playerPos.x - playerCollider->rect.w;
		app->render->camera.y = app->render->camera.h / 2 - playerPos.y;
	}*/

	// Max velocities
	//if (velocity.x > MAXVELOCITY_X)
	//	velocity.x = MAXVELOCITY_X;
	//if (velocity.x < -MAXVELOCITY_X)
	//	velocity.x = -MAXVELOCITY_X;
	//if (velocity.y > MAXVELOCITY_Y)
	//	velocity.y = MAXVELOCITY_Y;
	//if (velocity.y < -MAXVELOCITY_Y)
	//	velocity.y = -MAXVELOCITY_Y;
}

bool Player::PostUpdate()
{
	bool ret = true;

	if (currentAnim != NULL)
	{
		SDL_Rect rect = currentAnim->GetCurrentFrame();
		app->render->DrawTexture(*currentTexture, playerPos.x, playerPos.y, &rect);
	}

	return ret;
}

bool Player::OnCollision(Collider* c1, Collider* c2)
{
	bool ret = false;

	if (c2->type == Collider::Type::BLOCK)
	{
		if (((playerCollider->rect.y < c2->rect.y) || (playerCollider->rect.y > c2->rect.y)) && (playerCollider->rect.y + playerCollider->rect.h > c2->rect.y + c2->rect.h / 2))
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
			if ((playerCollider->rect.y + playerCollider->rect.h >= c2->rect.y) && (playerCollider->rect.y + playerCollider->rect.h <= c2->rect.y + 4))
			{
				playerPos.y = c2->rect.y - playerCollider->rect.h;
				isGround = true;
				isAir = false;
				LOG("Player feet on ground");
				ret = true;
			}
		}
	}
	else
	{
		isGround = false;
		isAir = true;
	}
	if (c2->type == Collider::Type::LAVA && godMode == false)
		destroyed = true;

	return ret;
}

bool Player::LoadState(pugi::xml_node& saveGameNode)
{
	bool ret = true;
	
	LOG("Loading Player state...");
	playerPos.x = saveGameNode.child("position").attribute("x").as_int();
	playerPos.y = saveGameNode.child("position").attribute("y").as_int();
	LOG("Player state succesfully loaded. \n Pos.x = %d; Pos.y = %d", playerPos.x, playerPos.y);

	return ret;
}

bool Player::SaveState(pugi::xml_node& saveGameNode) const
{
	bool ret = true;
	
	// Delete old content
	saveGameNode.remove_child("position");
	// Create new child with the new positions
	LOG("Saving Player state...");
	pugi::xml_node position = saveGameNode.append_child("position");
	position.append_attribute("x").set_value(playerPos.x);
	position.append_attribute("y").set_value(playerPos.y);
	LOG("Player state succesfully saved. \n Pos.x = %d; Pos.y = %d", playerPos.x, playerPos.y);

	return ret;
}

bool Player::CleanUp()
{
	bool ret = true;

	app->tex->UnLoad(idleTexture);
	app->tex->UnLoad(jumpTexture);
	app->tex->UnLoad(runTexture);
	app->tex->UnLoad(dieTexture);

	return ret;
}