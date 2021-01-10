#include "PauseScreen.h"

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

PauseScreen::PauseScreen(bool b) : Module(b)
{
	name = "Pause S";

	pause = { 185,0,962,720 };
}

PauseScreen::~PauseScreen() {}

bool PauseScreen::Start()
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
	pauseTex = app->tex->Load("Assets/textures/pause_menu.png");
	if (pauseTex == nullptr)
		ret = false;

	app->render->background = { 0,0,0,0 };

	app->player->playerPos = { -1000,-1000 };
	app->player->cameraFollow = false;

	font = new Font("Assets/Fonts/dungeon_font3.xml", app->tex);

	buttonResumeRect = { 225, 145, 165, 30 };
	buttonResume = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 1, buttonResumeRect); // New Game button (id = 1)
	buttonResume->SetObserver(this);

	buttonSettingsRect = { 225, 180, 140, 30 };
	buttonSettings = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 2, buttonSettingsRect); // Continue Game button (id = WIP)
	buttonSettings->SetObserver(this);

	buttonBackToMenuRect = { 230, 225, 165, 30 };
	buttonBackToMenu = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 3, buttonBackToMenuRect); // Settings button (id = WIP)
	buttonBackToMenu->SetObserver(this);

	buttonExitRect = { 260, 260, 120, 30 };
	buttonExit = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 4, buttonExitRect); // Credits button (id = WIP)
	buttonExit->SetObserver(this);

	return ret;
}

bool PauseScreen::Update(float dt)
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, (Module*)app->scene);
	}

	buttonResume->Update(dt);
	buttonSettings->Update(dt);
	buttonBackToMenu->Update(dt);
	buttonExit->Update(dt);

	return ret;
}

bool PauseScreen::PostUpdate()
{
	bool ret = true;

	if (exitRequested) return false;

	app->render->DrawTexture(pauseTex, 0, 0);

	buttonResume->Draw();
	if (buttonResume->state == GuiControlState::NORMAL)
		app->render->DrawText(font, "Resume", buttonResumeRect.x + 320, buttonResumeRect.y + 130, 90, 0, { 255, 255, 255, 255 });
	else if (buttonResume->state == GuiControlState::FOCUSED)
		app->render->DrawText(font, "Resume", buttonResumeRect.x + 320, buttonResumeRect.y + 130, 90, 0, { 255, 255, 0, 255 });
	else if (buttonResume->state == GuiControlState::PRESSED)
		app->render->DrawText(font, "Resume", buttonResumeRect.x + 320, buttonResumeRect.y + 130, 90, 0, { 255, 0, 0, 255 });

	buttonSettings->Draw();
	if (buttonSettings->state == GuiControlState::NORMAL)
		app->render->DrawText(font, "Settings", buttonSettingsRect.x + 310, buttonSettingsRect.y + 160, 90, 0, { 255, 255, 255, 255 });
	else if (buttonSettings->state == GuiControlState::FOCUSED)
		app->render->DrawText(font, "Settings", buttonSettingsRect.x + 310, buttonSettingsRect.y + 160, 90, 0, { 255, 255, 0, 255 });
	else if (buttonSettings->state == GuiControlState::PRESSED)
		app->render->DrawText(font, "Settings", buttonSettingsRect.x + 310, buttonSettingsRect.y + 160, 90, 0, { 255, 0, 0, 255 });

	buttonBackToMenu->Draw();
	if (buttonBackToMenu->state == GuiControlState::NORMAL)
		app->render->DrawText(font, "Back to Main Menu", buttonBackToMenuRect.x + 200, buttonBackToMenuRect.y + 200, 90, 0, { 255, 255, 255, 255 });
	else if (buttonBackToMenu->state == GuiControlState::FOCUSED)
		app->render->DrawText(font, "Back to Main Menu", buttonBackToMenuRect.x + 200, buttonBackToMenuRect.y + 200, 90, 0, { 255, 255, 0, 255 });
	else if (buttonBackToMenu->state == GuiControlState::PRESSED)
		app->render->DrawText(font, "Back to Main Menu", buttonBackToMenuRect.x + 200, buttonBackToMenuRect.y + 200, 90, 0, { 255, 0, 0, 255 });

	buttonExit->Draw();
	if (buttonExit->state == GuiControlState::NORMAL)
		app->render->DrawText(font, "Exit Game", buttonExitRect.x + 250, buttonExitRect.y + 250, 90, 0, { 255, 255, 255, 255 });
	else if (buttonExit->state == GuiControlState::FOCUSED)
		app->render->DrawText(font, "Exit Game", buttonExitRect.x + 250, buttonExitRect.y + 250, 90, 0, { 255, 255, 0, 255 });
	else if (buttonExit->state == GuiControlState::PRESSED)
		app->render->DrawText(font, "Exit Game", buttonExitRect.x + 250, buttonExitRect.y + 250, 90, 0, { 255, 0, 0, 255 });

	return ret;
}

bool PauseScreen::CleanUp()
{
	bool ret = true;

	startTime = 0;
	endTime = 0;
	actualTime = 0;

	if (!app->tex->UnLoad(pauseTex))
	{
		LOG("Start Screen -> Error unloading the texture.");
		ret = false;
	}

	return ret;
}

bool PauseScreen::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
		switch (control->id)
		{
		case 1:
			app->fade->FadeToBlack(this, (Module*)app->scene);
			break;
		case 2:
			app->fade->FadeToBlack(this, (Module*)app->settingsScreen);
			break;
		case 3:
			app->SaveGameRequest();
			app->fade->FadeToBlack(this, (Module*)app->titleScreen);
			break;
		case 4:
			exitRequested = true;
			break;
		default:
			break;
		}
	default:
		break;
	}

	return true;
}