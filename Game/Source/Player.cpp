#include "Player.h"

#include "App.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Audio.h"
#include "Log.h"
#include "Animation.h"

#include "Map.h"
#include "Scene.h"
#include "Window.h"

#include "SDL/include/SDL_scancode.h"

#define JUMPSPEED 50.0f
const float gravity = 60.0f + 50.0f;
const float deltaTime = 1.0f / 25.0f;

Player::Player() : Module()
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
	dieLeftAnim.loop = true;
	dieLeftAnim.speed = 0.1f;

	// Right Die Animation
	dieRightAnim.PushBack({ 16, 64, 16, 16 });
	dieRightAnim.PushBack({ 48, 64, 16, 16 });
	dieRightAnim.PushBack({ 80, 64, 16, 16 });
	dieRightAnim.PushBack({ 112, 64, 16, 16 });
	dieRightAnim.loop = true;
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

Player::~Player()
{

}


bool Player::Start()
{
	bool ret = true;

	LOG("Loading player textures...");
	texture = app->tex->Load("Assets/textures/Characters/Main/spritesheet.png");

	playerPos = { 32, 736 };
	position = { 32, 736 };
	collider = app->collisions->AddCollider({ position.x, position.y, 16,16 }, Collider::Type::PLAYER, this);
	playerCollider = app->collisions->AddCollider(SDL_Rect({ playerPos.x, playerPos.y, 16, 16 }), Collider::Type::PLAYER, this);

	currentTexture = &texture;
	currentAnim = &idleRightAnim;


	isGround = false;
	isAir = true;
	godMode = false;
	isDead = false;

	/*
	HAY QUE IMPLEMENTAR Y MODIFICAR EL PSD DEL JUMP
	jumpTexture = app->tex->Load("Assets/textures/Characters/Main1/Jump.png");
	*/

	/*
	HAY QUE IMPLEMENTAR Y MODIFICAR EL PSD DEL DIE
	dieTexture = app->tex->Load("Assets/textures/Characters/Main1/Die.png");
	*/


	//playerPos = { 32, 738 };

	//playerCollider = app->collisions->AddCollider(SDL_Rect({ playerPos.x, playerPos.y, 16, 14 }), Collider::Type::PLAYER, this);

	//currentAnim = &rightIdleAnim;
	//currentTexture = &idleTexture;
	//collisionExist = false;
	//isGround = false;
	//isAir = true;
	//collisionFromBelow = false;
	//godMode = true;

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
	if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT))
	{
		playerPos.x -= velocity.x;

		if (currentAnim != &runLeftAnim)
		{
			runLeftAnim.Reset();
			currentAnim = &runLeftAnim;
		}
	}

	if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT))
	{
		playerPos.x += velocity.x;

		if (currentAnim != &runRightAnim)
		{
			runRightAnim.Reset();
			currentAnim = &runRightAnim;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		playerPos.y -= velocity.y;
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		playerPos.y += velocity.y;
	}



	// Idle animations
	if (app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_UP)
	{
		currentAnim = &idleLeftAnim;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_UP)
	{
		currentAnim = &idleRightAnim;
	}



	// Debug Keys
	if (app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		destroyed = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		godMode = !godMode;
	}
}

void Player::Logic(float dt)
{
	/*if (!isGround)
	{

	}*/


	// If player is in ground
	/*if (isGround)
	{

	}*/
	// If player is in the air
	//if ((isAir || collisionExist == false) && !godMode && !destroyed)
	//{
	//	isGround = false;
	//	currentTexture = &jumpTexture;
	//	if (velocity.x >= 0)
	//		currentAnim = &jumpRightAnim;
	//	else currentAnim = &jumpLeftAnim;

	//	if (velocity.y <= -200)
	//		velocity.y += 100.0f * 4.0f * dt;
	//	else
	//		velocity.y += 100.0f * 3.0f * dt;

	//	velocity.x += -5.0f * velocity.x * dt;
	//}

	//// If player is in ground
	//if (isGround)
	//{
	//	if (currentAnim == &jumpRightAnim)
	//	{
	//		currentTexture = &idleTexture;
	//		currentAnim = &rightIdleAnim;
	//	}
	//	else if (currentAnim == &jumpLeftAnim)
	//	{
	//		currentTexture = &idleTexture;
	//		currentAnim = &leftIdleAnim;
	//	}
	//	if (isAir == false && godMode == false)
	//		velocity.y = 0;
	//	velocity.x += -1.0f * velocity.x * dt;
	//	if (fabs(velocity.x) < 0.01f)
	//		velocity.x = 0;


	// Animation changed if player dies
	
	if (destroyed == true)
	{
		if (velocity.x > 0)
			currentAnim = &dieRightAnim;
		if (velocity.x < 0)
			currentAnim = &dieLeftAnim;
	}

	// Setting collider position
	playerCollider->SetPos(position.x, position.y);

	// Borders for the player
	if (playerPos.x < 0)
		playerPos.x = 0;
	if (playerPos.x + playerCollider->rect.w > 100 * 16)
		playerPos.x = 100 * 16 - playerCollider->rect.w;
	if (playerPos.y < 0)
		playerPos.y = 0;
	if (playerPos.y + playerCollider->rect.h > 50 * 16)
		playerPos.y = 50 * 16 - playerCollider->rect.y;
	

	// Setting collider position && player position
	playerCollider->SetPos(playerPos.x, playerPos.y);
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

	//if (c2->type == Collider::Type::BLOCK)
	//{
	//	isGround = true;
	//	isAir = false;
	//	isJumping = false;
	//	if (position.y + playerCollider->rect.h - 1 >= c2->rect.y)
	//	{
	//		position.y = c2->rect.y - playerCollider->rect.h + 1;
	//		velocity.y = 0;
	//	}

	//}
	//else
	//{
	//	if (((playerCollider->rect.y < c2->rect.y) || (playerCollider->rect.y > c2->rect.y)) && (playerCollider->rect.y + playerCollider->rect.h > c2->rect.y + c2->rect.h / 2))
	//	{
	//		collisionFromBelow = true;
	//		LOG("Player through the ground");
	//		ret = false;
	//	}
	//	else
	//		collisionFromBelow = false;

	//	if (collisionFromBelow == false)
	//	{
	//		// Maintain the feet to the ground
	//		if ((playerCollider->rect.y + playerCollider->rect.h >= c2->rect.y) && (playerCollider->rect.y + playerCollider->rect.h <= c2->rect.y + 4))
	//		{
	//			playerPos.y = c2->rect.y - playerCollider->rect.h;
	//			isGround = true;
	//			isAir = false;
	//			LOG("Player feet on ground");
	//			ret = true;
	//		}
	//	}
	//}
	//else
	//{
	//	isGround = false;
	//	isAir = true;
	//}
	//if (c2->type == Collider::Type::LAVA && godMode == false)
	//	destroyed = true;

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
	pugi::xml_node positionNode = saveGameNode.append_child("position");
	positionNode.append_attribute("x").set_value(position.x);
	positionNode.append_attribute("y").set_value(position.y);
	LOG("Player state succesfully saved. \n Pos.x = %d; Pos.y = %d", position.x, position.y);

	return ret;
}

bool Player::CleanUp()
{
	bool ret = true;

	app->tex->UnLoad(texture);

	return ret;
}