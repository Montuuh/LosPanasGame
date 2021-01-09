#include "ModuleInitialScreen.h"
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


ModuleInitialScreen::ModuleInitialScreen(bool b) : Module(b)
{
	name = "Initial S";

	logo = { 185, 0, 962, 720 };
}

ModuleInitialScreen::~ModuleInitialScreen() {}

bool ModuleInitialScreen::Start()
{
	bool ret = true;

	startTime = SDL_GetTicks();
	actualTime = 0;
	endTime = 3000;

	// Include logo

	logoTex = app->tex->Load("Assets/textures/logo_screen.png");
	app->render->background = { 0,0,0,0 };
	if (logoTex == nullptr)
	if (logoTex == nullptr)
	{
		ret = false;
	}

	app->player->playerPos = { -1000,-1000 };
	app->player->cameraFollow = false;
	return ret;
}

bool ModuleInitialScreen::Update(float dt)
{
	bool ret = true;

	timer += 1.0f;
	if (timer >= 180.0f) // ~= 4 secs
		app->fade->FadeToBlack(this, (Module*)app->titleScreen);

	return ret;
}

bool ModuleInitialScreen::PostUpdate()
{
	bool ret = true;

	app->render->DrawTexture(logoTex, 0, 0);

	return ret;
}

bool ModuleInitialScreen::CleanUp()
{
	bool ret = true;

	startTime = 0;
	endTime = 0;
	actualTime = 0;

	if (!app->tex->UnLoad(logoTex))
	{
		LOG("Start Screen -> Error unloading the texture.");
		ret = false;
	}

	return ret;
}