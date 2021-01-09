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
#include "Font.h"

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


	

	app->audio->PlayMusic("Assets/Audio/Music/wii_music.ogg");

	titleTex = app->tex->Load("Assets/textures/intro_screen.png");
	if (titleTex == nullptr)
		ret = false;

	app->render->background = { 0,0,0,0 };

	app->player->playerPos = { -1000,-1000 };
	app->player->cameraFollow = false;

	font = new Font("Assets/Fonts/dungeon_font3.xml", app->tex);

	//buttonNewGameRect = { 200, 159, 216, 30 };
	//buttonNewGame = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 1, buttonNewGameRect); // New Game button (id = 1)
	//buttonNewGame->SetObserver(this);

	//buttonExitRect = { 220, 312, 175, 30 };
	//buttonExit = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 5, buttonExitRect); // Exit Game button (id = 5)
	//buttonExit->SetObserver(this);

	buttonNewGameRect = { 50, 300, 150, 30 };
	buttonNewGame = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 1, buttonNewGameRect); // New Game button (id = 1)
	buttonNewGame->SetObserver(this);

	buttonExitRect = { 420, 300, 175, 30 };
	buttonExit = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 5, buttonExitRect); // Exit Game button (id = 5)
	buttonExit->SetObserver(this);

	return ret;
}

bool TitleScreen::Update(float dt)
{
	bool ret = true;

	buttonNewGame->Update(dt);
	buttonExit->Update(dt);

	return ret;
}

bool TitleScreen::PostUpdate()
{
	bool ret = true;
	
	if (exitRequested) return false;

	app->render->DrawTexture(titleTex, 0, 0);

	//buttonNewGame->Draw();
	//if (buttonNewGame->state == GuiControlState::NORMAL)
	//	app->render->DrawText(font, "New Game", buttonNewGameRect.x + 190, buttonNewGameRect.y + 110, 170, 0, { 255, 255, 255, 255 });
	//else if (buttonNewGame->state == GuiControlState::FOCUSED)
	//	app->render->DrawText(font, "New Game", buttonNewGameRect.x + 190, buttonNewGameRect.y + 110, 170, 0, { 255, 255, 0, 255 });
	//else if(buttonNewGame->state == GuiControlState::PRESSED)
	//	app->render->DrawText(font, "New Game", buttonNewGameRect.x + 190, buttonNewGameRect.y + 110, 170, 0, { 255, 0, 0, 255 });

	//buttonExit->Draw();
	//if (buttonExit->state == GuiControlState::NORMAL)
	//	app->render->DrawText(font, "Exit Game", buttonExitRect.x + 225, buttonExitRect.y + 280, 130, 0, { 255, 255, 255, 255 });
	//else if (buttonExit->state == GuiControlState::FOCUSED)
	//	app->render->DrawText(font, "Exit Game", buttonExitRect.x + 225, buttonExitRect.y + 280, 130, 0, { 255, 255, 0, 255 });
	//else if (buttonExit->state == GuiControlState::PRESSED)
	//	app->render->DrawText(font, "Exit Game", buttonExitRect.x + 225, buttonExitRect.y + 280, 130, 0, { 255, 0, 0, 255 });

	buttonNewGame->Draw();
	if (buttonNewGame->state == GuiControlState::NORMAL)
		app->render->DrawText(font, "New Game", buttonNewGameRect.x + 190, buttonNewGameRect.y + 110, 170, 0, { 255, 255, 255, 255 });
	else if (buttonNewGame->state == GuiControlState::FOCUSED)
		app->render->DrawText(font, "New Game", buttonNewGameRect.x + 190, buttonNewGameRect.y + 110, 170, 0, { 255, 255, 0, 255 });
	else if (buttonNewGame->state == GuiControlState::PRESSED)
		app->render->DrawText(font, "New Game", buttonNewGameRect.x + 190, buttonNewGameRect.y + 110, 170, 0, { 255, 0, 0, 255 });

	buttonExit->Draw();
	if (buttonExit->state == GuiControlState::NORMAL)
		app->render->DrawText(font, "Exit Game", buttonExitRect.x + 225, buttonExitRect.y + 280, 130, 0, { 255, 255, 255, 255 });
	else if (buttonExit->state == GuiControlState::FOCUSED)
		app->render->DrawText(font, "Exit Game", buttonExitRect.x + 225, buttonExitRect.y + 280, 130, 0, { 255, 255, 0, 255 });
	else if (buttonExit->state == GuiControlState::PRESSED)
		app->render->DrawText(font, "Exit Game", buttonExitRect.x + 225, buttonExitRect.y + 280, 130, 0, { 255, 0, 0, 255 });

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
	switch (control->type)
	{
		case GuiControlType::BUTTON:
			switch (control->id)
			{
				case 1:
					app->fade->FadeToBlack(this, (Module*)app->deathScene);
					break;
				case 5:
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