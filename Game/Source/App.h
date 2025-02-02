#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "PerfTimer.h"
#include "Timer.h"

#include "List.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Scene;
class DeathScene;
class WinScreen;
class ModuleFonts;
class ModuleDebugInfo;
class ModuleFadeToBlack;
class TitleScreen;
class ModulePlayer;
class Map;
class ModuleInitialScreen;
class ModuleCollisions;
class Entities;
class ModuleHud;
class ModuleParticles;
class PathFinding;
class GuiManager;
class PauseScreen;
class SettingsScreen;
class TitleSettingsScreen;
class CreditsScreen;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

    // L02: DONE 1: Create methods to request Load / Save
	void LoadGameRequest();
	void SaveGameRequest() const;

private:

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGame();
	bool SaveGame() const;

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;

	Scene* scene;
	TitleScreen* titleScreen;
	ModuleInitialScreen* initialScreen;
	DeathScene* deathScene;
	WinScreen* winScreen;
	ModuleHud* hud;
	Map* map;
	ModulePlayer* player;
	PathFinding* pathfinding;
	PauseScreen* pauseScreen;
	SettingsScreen* settingsScreen;
	TitleSettingsScreen* titlesettingsScreen;
	CreditsScreen* creditsScreen;

	ModuleCollisions* collisions;
	ModuleParticles* particles;

	ModuleDebugInfo* debug;
	ModuleFadeToBlack* fade;
	Entities* entities;
	GuiManager* guimanager;

	float cappedMs = -1;
private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;

	// L01: DONE 2: Create new variables from pugui namespace
	// NOTE: Redesigned LoadConfig() to avoid storing this variables
	//pugi::xml_document configFile;
	//pugi::xml_node config;
	//pugi::xml_node configApp;

	uint frames;

	mutable bool saveGameRequested;
	bool loadGameRequested;

	// L07: TODO 4: Calculate some timing measures
	// required variables are provided:
	PerfTimer ptimer;
	uint64 frameCount = 0;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;
	uint32 lastSecFrameCount = 0;
	uint32 prevLastSecFrameCount = 0;
	float dt = 0.0f;

	
	int newMaxFramerate = 0;
};

extern App* app;

#endif	// __APP_H__