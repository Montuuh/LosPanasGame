#include "DeathScene.h"

#include "App.h"
#include "Textures.h"
#include "ModuleFadeToBlack.h"
#include "Input.h"
#include "TitleScreen.h"
#include "Window.h"
#include "Render.h"
#include "Audio.h"
#include "ModulePlayer.h"
#include "Log.h"
#include "ModuleHud.h"

DeathScene::DeathScene(bool b) : Module(b)
{
	name = "Death S";

	deathRect = { 185, 0, 962, 720 };
}

DeathScene::~DeathScene() {}

bool DeathScene::Start()
{
	bool ret = true;

	if (app->hud->IsEnabled() == true)
	{
		app->hud->Disable();
	}

	startTime = SDL_GetTicks();
	actualTime = 0;
	endTime = 3000;

	app->render->background = { 0,0,0,0 };
	// Include logo
	app->render->camera = { 0,0,1280,720 };
	deathTex = app->tex->Load("Assets/Textures/death_screen.png");

	if (deathTex == nullptr)
	{
		ret = false;
	}

	app->render->camera = { 0,0,1280,720 };
	app->player->cameraFollow = false;

	return ret;
}

bool DeathScene::Update(float dt)
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, (Module*)app->titleScreen);
	}

	return ret;
}

bool DeathScene::PostUpdate()
{
	bool ret = true;
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	app->render->DrawTexture(deathTex, 0,0);
	return ret;
}

bool DeathScene::CleanUp()
{
	bool ret = true;

	startTime = 0;
	endTime = 0;
	actualTime = 0;

	if (!app->tex->UnLoad(deathTex))
	{
		LOG("Start Screen -> Error unloading the texture.");
		ret = false;
	}

	return ret;
}