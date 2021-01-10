#include "TitleSettingsScreen.h"

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

TitleSettingsScreen::TitleSettingsScreen(bool b) : Module(b)
{
	name = "Settings S";

	titleSettings = { 185,0,962,720 };
}

TitleSettingsScreen::~TitleSettingsScreen() {}

bool TitleSettingsScreen::Start()
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
	titleSettingsTex = app->tex->Load("Assets/textures/titlesettings_menu.png");
	skull = app->tex->Load("Assets/textures/skull.png");
	tickTex = app->tex->Load("Assets/textures/ticks.png");
	if (titleSettingsTex == nullptr)
		ret = false;

	app->render->background = { 0,0,0,0 };

	app->player->playerPos = { -1000,-1000 };
	app->player->cameraFollow = false;

	font = new Font("Assets/Fonts/dungeon_font3.xml", app->tex);

	musicVolume = (GuiSlider*)app->guimanager->CreateGuiControl(GuiControlType::SLIDER, 2, {325, 90, 220, 30});
	musicVolume->anim.PushBack({ 0, 0, 29, 40 });
	musicVolume->anim.PushBack({ 0, 0, 29, 40 });
	musicVolume->anim.PushBack({ 0, 0, 29, 40 });
	musicVolume->SetTexture(skull);
	musicVolume->SetObserver(this);

	fxVolume = (GuiSlider*)app->guimanager->CreateGuiControl(GuiControlType::SLIDER, 3, { 325, 139, 220, 30 });
	fxVolume->anim.PushBack({ 0, 0, 29, 40 });
	fxVolume->anim.PushBack({ 0, 0, 29, 40 });
	fxVolume->anim.PushBack({ 0, 0, 29, 40 });
	fxVolume->SetTexture(skull);
	fxVolume->SetObserver(this);

	buttonBackRect = { 450, 300, 140, 30 };
	buttonBack = (GuiButton*)app->guimanager->CreateGuiControl(GuiControlType::BUTTON, 1, buttonBackRect); // Back button (id = WIP)
	buttonBack->SetObserver(this);

	checkBoxFullScreen = (GuiCheckBox*)app->guimanager->CreateGuiControl(GuiControlType::CHECKBOX, 4, { 335, 205, 35, 35 });
	checkBoxFullScreen->SetObserver(this);
	checkBoxFullScreen->SetTexture(tickTex);
	checkBoxFullScreen->anim.PushBack({ 34,0,34,32 }); // Normal with tick
	checkBoxFullScreen->anim.PushBack({ 0,0,34,32 }); // Normal without tick
	checkBoxFullScreen->anim.PushBack({ 68,0,34,32 }); // Focused with tick
	checkBoxFullScreen->anim.PushBack({ 0,0,34,32 }); // Focused without tick
	checkBoxFullScreen->anim.PushBack({ 102,0,34,32 }); // Pressed with tick
	checkBoxFullScreen->anim.PushBack({ 0,0,34,32 }); // Pressed without tick

	checkBoxVsync = (GuiCheckBox*)app->guimanager->CreateGuiControl(GuiControlType::CHECKBOX, 5, { 335, 254, 35, 35 });
	checkBoxVsync->SetObserver(this);
	checkBoxVsync->SetTexture(tickTex);
	checkBoxVsync->anim.PushBack({ 34,0,34,32 }); // Normal with tick
	checkBoxVsync->anim.PushBack({ 0,0,34,32 }); // Normal without tick
	checkBoxVsync->anim.PushBack({ 68,0,34,32 }); // Focused with tick
	checkBoxVsync->anim.PushBack({ 0,0,34,32 }); // Focused without tick
	checkBoxVsync->anim.PushBack({ 102,0,34,32 }); // Pressed with tick
	checkBoxVsync->anim.PushBack({ 0,0,34,32 }); // Pressed without tick

	return ret;
}

bool TitleSettingsScreen::Update(float dt)
{
	bool ret = true;

	buttonBack->Update(dt);

	musicVolume->Update(app->input, dt);
	fxVolume->Update(app->input, dt);

	app->audio->ChangeMusicVolume(musicVolume->value);
	app->audio->ChangeFxVolume(fxVolume->value);

	checkBoxFullScreen->Update(dt);
	checkBoxVsync->Update(dt);

	return ret;
}

bool TitleSettingsScreen::PostUpdate()
{
	bool ret = true;

	if (exitRequested) return false;

	app->render->DrawTexture(titleSettingsTex, 0, 0);

	buttonBack->Draw();
	if (buttonBack->state == GuiControlState::NORMAL)
		app->render->DrawText(font, "Back", buttonBackRect.x + 500, buttonBackRect.y + 270, 130, 0, { 255, 255, 255, 255 });
	else if (buttonBack->state == GuiControlState::FOCUSED)
		app->render->DrawText(font, "Back", buttonBackRect.x + 500, buttonBackRect.y + 270, 130, 0, { 255, 255, 0, 255 });
	else if (buttonBack->state == GuiControlState::PRESSED)
		app->render->DrawText(font, "Back", buttonBackRect.x + 500, buttonBackRect.y + 270, 130, 0, { 255, 0, 0, 255 });

	musicVolume->DrawDebug(app->render);
	musicVolume->Draw(app->render);
	fxVolume->DrawDebug(app->render);
	fxVolume->Draw(app->render);

	checkBoxFullScreen->DrawDebug();
	checkBoxFullScreen->DrawTexture();
	checkBoxVsync->DrawDebug();
	checkBoxVsync->DrawTexture();
	

	return ret;
}

bool TitleSettingsScreen::CleanUp()
{
	bool ret = true;

	startTime = 0;
	endTime = 0;
	actualTime = 0;

	app->guimanager->DestroyGuiControl(musicVolume);
	app->guimanager->DestroyGuiControl(fxVolume);

	app->guimanager->DestroyGuiControl(checkBoxFullScreen);
	app->guimanager->DestroyGuiControl(checkBoxVsync);


	if (!app->tex->UnLoad(titleSettingsTex))
	{
		LOG("Start Screen -> Error unloading the texture.");
		ret = false;
	}

	return ret;
}

bool TitleSettingsScreen::OnGuiMouseClickEvent(GuiControl* control)
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