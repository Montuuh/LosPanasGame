#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

#include "Module.h"
#include "GuiControl.h"

#include "List.h"

class GuiManager : public Module
{
public:

	GuiManager();

	virtual ~GuiManager();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	GuiControl* CreateGuiControl(GuiControlType type, int id, SDL_Rect bounds);
	void DestroyGuiControl(GuiControl* entity);

	void AddGuiControl(GuiControl* entity);

	void UpdateAll(float dt, bool doLogic);

	void DrawAll();
public:

	List<GuiControl*> controls;

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;
	int id = 0;
	SDL_Texture* titleScreenTexGui;
};

#endif

