#include "WinScreen.h"

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

WinScreen::WinScreen(bool b) : Module(b)
{
	name = "Initial S";

	winRect = { 185, 0, 962, 720 };
}

WinScreen::~WinScreen() {}

bool WinScreen::Start()
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
	winTex = app->tex->Load("Assets/Textures/win_screen.png");

	if (winTex == nullptr)
	{
		ret = false;
	}

	app->render->camera = { 0,0,1280,720 };
	app->player->cameraFollow = false;
	return ret;
}

bool WinScreen::Update(float dt)
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, (Module*)app->titleScreen);
	}

	return ret;
}

bool WinScreen::PostUpdate()
{
	bool ret = true;
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	app->render->DrawTexture(winTex, 0, 0);
	return ret;
}

bool WinScreen::CleanUp()
{
	bool ret = true;

	startTime = 0;
	endTime = 0;
	actualTime = 0;

	if (!app->tex->UnLoad(winTex))
	{
		LOG("Start Screen -> Error unloading the texture.");
		ret = false;
	}

	return ret;
}