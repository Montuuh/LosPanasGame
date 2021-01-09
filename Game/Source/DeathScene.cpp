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
#include "Font.h"
#include "GuiManager.h"

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

	app->render->camera = { 0,0,1280,720 };
	deathTex = app->tex->Load("Assets/Textures/death_screen.png");
	if (deathTex == nullptr)
	{
		ret = false;
	}

	app->render->background = { 0,0,0,0 };
	app->render->camera = { 0,0,1280,720 };
	app->player->cameraFollow = false;

	font = new Font("Assets/Fonts/dungeon_font3.xml", app->tex);
	buttonBackToMainMenuRect = { 50, 300, 150, 30 };
	buttonBackToMainMenu = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 1, buttonBackToMainMenuRect); // Main menu button (id = 1)
	buttonBackToMainMenu->SetObserver(this);
	buttonExitRect = { 420, 300, 175, 30 };
	buttonExit = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 2, buttonExitRect); // Exit Game button (id = 2)
	buttonExit->SetObserver(this);



	return ret;
}

bool DeathScene::Update(float dt)
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, (Module*)app->titleScreen);
	}

	buttonBackToMainMenu->Update(dt);
	buttonExit->Update(dt);

	return ret;
}

bool DeathScene::PostUpdate()
{
	bool ret = true;

	if (app->titleScreen->exitRequested) return false;

	app->render->DrawTexture(deathTex, 0,0);

	buttonBackToMainMenu->Draw();
	if (buttonBackToMainMenu->state == GuiControlState::NORMAL)
		app->render->DrawText(font, "Main Menu", buttonBackToMainMenuRect.x + 225, buttonBackToMainMenuRect.y + 280, 90, 0, { 255, 255, 255, 255 });
	else if (buttonBackToMainMenu->state == GuiControlState::FOCUSED)
		app->render->DrawText(font, "Main Menu", buttonBackToMainMenuRect.x + 225, buttonBackToMainMenuRect.y + 280, 90, 0, { 255, 255, 0, 255 });
	else if (buttonBackToMainMenu->state == GuiControlState::PRESSED)
		app->render->DrawText(font, "Main Menu", buttonBackToMainMenuRect.x + 225, buttonBackToMainMenuRect.y + 280, 90, 0, { 255, 0, 0, 255 });

	buttonExit->Draw();
	if (buttonExit->state == GuiControlState::NORMAL)
		app->render->DrawText(font, "Exit Game", buttonExitRect.x + 225, buttonExitRect.y + 280, 90, 0, { 255, 255, 255, 255 });
	else if (buttonExit->state == GuiControlState::FOCUSED)
		app->render->DrawText(font, "Exit Game", buttonExitRect.x + 225, buttonExitRect.y + 280, 90, 0, { 255, 255, 0, 255 });
	else if (buttonExit->state == GuiControlState::PRESSED)
		app->render->DrawText(font, "Exit Game", buttonExitRect.x + 225, buttonExitRect.y + 280, 90, 0, { 255, 0, 0, 255 });

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

bool DeathScene::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
		switch (control->id)
		{
		case 1:
			app->fade->FadeToBlack(this, (Module*)app->titleScreen);
			break;
		case 2:
			app->titleScreen->exitRequested = true;
			break;
		default:
			break;
		}
	default:
		break;
	}

	return true;
}