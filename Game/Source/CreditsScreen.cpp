#include "CreditsScreen.h"

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
#include "Font.h"
#include "GuiManager.h"

CreditsScreen::CreditsScreen(bool b) : Module(b)
{
	name = "Credits S";

	credits = { 185,0,962,720 };
}

CreditsScreen::~CreditsScreen() {}

bool CreditsScreen::Start()
{
	bool ret = true;

	if (app->hud->IsEnabled() == true)
	{
		app->hud->Disable();
	}

	startTime = SDL_GetTicks();
	actualTime = 0;
	endTime = 3000;

	app->render->camera = { 0,0,1280,720 };
	creditsTex = app->tex->Load("Assets/textures/credits_screen.png");
	if (creditsTex == nullptr)
		ret = false;

	app->render->background = { 0,0,0,0 };

	app->player->playerPos = { -1000,-1000 };
	app->player->cameraFollow = false;

	font = new Font("Assets/Fonts/dungeon_font3.xml", app->tex);

	buttonBackRect = { 450, 300, 140, 30 };
	buttonBack = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 1, buttonBackRect); // Back button (id = WIP)
	buttonBack->SetObserver(this);

	return ret;
}

bool CreditsScreen::Update(float dt)
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, (Module*)app->titleScreen);
	}

	buttonBack->Update(dt);

	return ret;
}

bool CreditsScreen::PostUpdate()
{
	bool ret = true;

	if (exitRequested) return false;

	app->render->DrawTexture(creditsTex, 0, 0);

	buttonBack->Draw();
	if (buttonBack->state == GuiControlState::NORMAL)
		app->render->DrawText(font, "Back", buttonBackRect.x + 500, buttonBackRect.y + 270, 130, 0, { 255, 255, 255, 255 });
	else if (buttonBack->state == GuiControlState::FOCUSED)
		app->render->DrawText(font, "Back", buttonBackRect.x + 500, buttonBackRect.y + 270, 130, 0, { 255, 255, 0, 255 });
	else if (buttonBack->state == GuiControlState::PRESSED)
		app->render->DrawText(font, "Back", buttonBackRect.x + 500, buttonBackRect.y + 270, 130, 0, { 255, 0, 0, 255 });

	return ret;
}

bool CreditsScreen::CleanUp()
{
	bool ret = true;

	startTime = 0;
	endTime = 0;
	actualTime = 0;

	if (!app->tex->UnLoad(creditsTex))
	{
		LOG("Start Screen -> Error unloading the texture.");
		ret = false;
	}

	return ret;
}

bool CreditsScreen::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
		switch (control->id)
		{
		case 1:
			app->fade->FadeToBlack(this, (Module*)app->titleScreen);
			break;
		default:
			break;
		}
	default:
		break;
	}

	return true;
}