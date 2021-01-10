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
#include "Font.h"
#include "GuiManager.h"
#include "Audio.h"

WinScreen::WinScreen(bool b) : Module(b)
{
	name = "Win S";

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

	app->render->camera = { 0,0,1280,720 };
	winTex = app->tex->Load("Assets/Textures/win_screen.png");
	if (winTex == nullptr)
	{
		ret = false;
	}
	
	/*app->audio->PlayFx()*/

	app->render->background = { 0,0,0,0 };
	app->render->camera = { 0,0,1280,720 };
	app->player->cameraFollow = false;

	font = new Font("Assets/Fonts/dungeon_font3.xml", app->tex);
	buttonBackToMainMenuRect = { 50, 300, 150, 30 };
	buttonBackToMainMenu = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 1, buttonBackToMainMenuRect); // Main menu button (id = 1)
	buttonBackToMainMenu->SetObserver(this);

	buttonPlayAgainRect = { 420, 300, 175, 30 };
	buttonPlayAgain = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 2, buttonPlayAgainRect); // Exit Game button (id = 2)
	buttonPlayAgain->SetObserver(this);



	return ret;
}

bool WinScreen::Update(float dt)
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, (Module*)app->titleScreen);
	}

	buttonBackToMainMenu->Update(dt);
	buttonPlayAgain->Update(dt);

	return ret;
}

bool WinScreen::PostUpdate()
{
	bool ret = true;

	if (exitRequested) return false;

	app->render->DrawTexture(winTex, 0, 0);

	buttonBackToMainMenu->Draw();
	if (buttonBackToMainMenu->state == GuiControlState::NORMAL)
		app->render->DrawText(font, "Main Menu", buttonBackToMainMenuRect.x + 75, buttonBackToMainMenuRect.y + 280, 90, 0, { 255, 255, 255, 255 });
	else if (buttonBackToMainMenu->state == GuiControlState::FOCUSED)
		app->render->DrawText(font, "Main Menu", buttonBackToMainMenuRect.x + 75, buttonBackToMainMenuRect.y + 280, 90, 0, { 255, 255, 0, 255 });
	else if (buttonBackToMainMenu->state == GuiControlState::PRESSED)
		app->render->DrawText(font, "Main Menu", buttonBackToMainMenuRect.x + 75, buttonBackToMainMenuRect.y + 280, 90, 0, { 255, 0, 0, 255 });

	buttonPlayAgain->Draw();
	if (buttonPlayAgain->state == GuiControlState::NORMAL)
		app->render->DrawText(font, "Play Again", buttonPlayAgainRect.x + 475, buttonPlayAgainRect.y + 280, 90, 0, { 255, 255, 255, 255 });
	else if (buttonPlayAgain->state == GuiControlState::FOCUSED)
		app->render->DrawText(font, "Play Again", buttonPlayAgainRect.x + 475, buttonPlayAgainRect.y + 280, 90, 0, { 255, 255, 0, 255 });
	else if (buttonPlayAgain->state == GuiControlState::PRESSED)
		app->render->DrawText(font, "Play Again", buttonPlayAgainRect.x + 475, buttonPlayAgainRect.y + 280, 90, 0, { 255, 0, 0, 255 });

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

bool WinScreen::OnGuiMouseClickEvent(GuiControl* control)
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
			app->fade->FadeToBlack(this, (Module*)app->scene);
			break;
		default:
			break;
		}
	default:
		break;
	}

	return true;
}