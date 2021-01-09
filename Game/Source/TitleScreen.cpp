#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "TitleScreen.h"
#include "ModuleFadeToBlack.h"
#include "Scene.h"
#include "ModulePlayer.h"
#include "GuiManager.h"

#include "Defs.h"
#include "Log.h"

TitleScreen::TitleScreen(bool b) : Module(b)
{
	name = "Title S";

	title = { 185,0,962,720 };
}

TitleScreen::~TitleScreen() {}

bool TitleScreen::Start()
{
	bool ret = true;

	startTime = SDL_GetTicks();
	actualTime = 0;
	endTime = 3000;

	// Include title

	app->audio->PlayMusic("Assets/Audio/Music/wii_music.ogg");

	titleTex = app->tex->Load("Assets/textures/intro_screen.png");
	app->render->background = { 0,0,0,0 };
	if (titleTex == nullptr)
	{
		ret = false;
	}

	buttonNewGame = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 1, { 0, 0, 100, 100 });

	app->player->playerPos = { -1000,-1000 };
	app->player->cameraFollow = false;
	return ret;
}

bool TitleScreen::Update(float dt)
{
	bool ret = true;

	buttonNewGame->Update(dt);

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, (Module*)app->scene);
	}

	return ret;
}

bool TitleScreen::PostUpdate()
{
	bool ret = true;
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	actualTime = SDL_GetTicks() - startTime;

	buttonNewGame->Draw();

	if (actualTime < endTime)
	{

	}
	app->render->DrawTexture(titleTex, 0, 0);
	return ret;
}

bool TitleScreen::CleanUp()
{
	bool ret = true;

	startTime = 0;
	endTime = 0;
	actualTime = 0;

	if (!app->tex->UnLoad(titleTex))
	{
		LOG("Start Screen -> Error unloading the texture.");
		ret = false;
	}

	return ret;
}

bool TitleScreen::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->id)
	{
	case 1://NewGame
		app->fade->FadeToBlack(this, (Module*)app->scene);
		break;
	}
	return true;
}