#include "App.h"
#include "Audio.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "ModuleFadeToBlack.h"
#include "ModuleHud.h"
#include "Map.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEntities.h"
#include "ModuleParticles.h"

#include "Defs.h"
#include "Log.h"
#include "ModulePlayer.h"

Scene::Scene() : Module(true) // The argument passed to the parent constructor is if it is enabled at construction
{
	name.Create("scene");
	img = bg = NULL;
}

Scene::Scene(bool b) : Module(b) // The argument passed to the parent constructor is if it is enabled at construction
{
	name.Create("scene");
	img = bg = NULL;

}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	app->map->Load("level1.tmx");

	app->render->background = { 200,210,222,0 };
	app->audio->PlayMusic("Assets/Audio/Music/wii_music.ogg");
	
	if (app->collisions->IsEnabled() == false)
		app->collisions->Enable();

	if (app->player->IsEnabled() == false)
		app->player->Enable();

	if (app->entities->IsEnabled() == false)
		app->entities->Enable();

	//if (app->particles->IsEnabled() == false)
	//	app->particles->Enable();

	if (app->hud->IsEnabled() == false)
	{
		app->hud->Enable();
	}
	app->map->LoadColliders();

	app->player->destroyed = false;
	app->player->hasWon = false;
	app->player->playerPos = { 4*16, 46*16 };
	
	app->player->velocity.y = 0;
	app->player->cameraFollow = true;
	app->player->lives = 3;


	app->entities->AddEntity(EntityType::ITEM_HEALTH, 73 * 16, 31 * 16);
	app->entities->AddEntity(EntityType::ITEM_DIAMOND, 88 * 16, 18 * 16);
	app->entities->AddEntity(EntityType::ITEM_DIAMOND, 83 * 16, 10 * 16);
	//app->entities->AddEntity(EntityType::ITEM_DIAMOND, 48 * 16, 7 * 16);
	app->entities->AddEntity(EntityType::ITEM_DIAMOND, 77 * 16, 25 * 16);

	counterSeconds = 0;

	app->SaveGameRequest();
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	// The camera follows player(at the center)
	if (app->win->GetScale() == 1)
	{
		app->render->camera.x = app->render->camera.w / 2 - app->player->playerPos.x;
		app->render->camera.y = app->render->camera.h / 2 - app->player->playerPos.y;
	}
	else if (app->win->GetScale() == 2)
	{
		app->render->camera.x = app->render->camera.w / 2 - app->player->playerPos.x * app->win->GetScale();
		app->render->camera.y = app->render->camera.h / 2 - app->player->playerPos.y * app->win->GetScale();
	}


    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y += 10;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y -= 10;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x += 30;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x -= 30;
		
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_UP || app->input->GetKey(SDL_SCANCODE_F3) == KEY_UP)
		app->fade->FadeToBlack(this, (Module*)app->scene);

	if (app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		app->player->lives = 0;
	}

	if (app->player->destroyed == true)
	{
		if (app->player->lives == 0)
		{
			if (counterSeconds == 60)
			{
				app->fade->FadeToBlack(this, (Module*)app->deathScene);
				counterSeconds = 0;
			}
		++counterSeconds;
		}	
	}
	if (app->player->hasWon == true)
	{
		if (counterSeconds == 60)
		{
			app->fade->FadeToBlack(this, (Module*)app->winScreen);
			counterSeconds = 0;
		}
		counterSeconds++;
	}

	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		app->fade->FadeToBlack(this, (Module*)app->pauseScreen);
		counterSeconds += dt;
	}

	if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		if (capFrameRate)
		{
			storeFrameRateCap = app->cappedMs;
			app->cappedMs = 1000 / 30;
			capFrameRate = false;
		}
		else
		{
			app->cappedMs = storeFrameRateCap;
			capFrameRate = true;
		}
	}
	
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->data.width, app->map->data.height,
				   app->map->data.tileWidth, app->map->data.tileHeight,
				   app->map->data.tilesets.Count());

	//app->win->SetTitle(title.GetString());
	iPoint mapPos = app->map->WorldToMap(app->player->playerPos.x, app->player->playerPos.y);
	
	// Set the camera limits
	if (app->render->camera.x > 0) app->render->camera.x = 0;
	if (app->render->camera.x < -1600 * 6 / 5) app->render->camera.x = -1600 * 6 / 5;
	if (app->render->camera.y > 0) app->render->camera.y = 0;
	if (app->render->camera.y < -800 * 1.1) app->render->camera.y = -800 * 1.1;

	return true;
}

bool Scene::OnGuiMouseClickEvent(GuiControl* control)
{
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	app->map->Draw();
	return ret;
}


// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(bg);
	app->player->Disable();
	app->collisions->Disable();
	app->entities->Disable();
	/*app->particles->Disable();*/
	app->map->CleanUp();
	
	return true;
}
