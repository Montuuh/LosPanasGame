#ifndef __DEATH_SCENE_H__
#define __DEATH_SCENE_H__

//#include "SDL/include/SDL_rect.h"
//#ifdef _DEBUG
//#pragma comment( lib, "Source/External/SDL/include/SDL_rect.h")
//#else
//#pragma comment( lib, "Source/External/SDL/include/SDL_rect.h")
//#endif

#include "Module.h"
#include "Textures.h"
#include "GuiButton.h"

struct SDL_Rect;
class Font;

class DeathScene : public Module
{

public:

	DeathScene(bool startEnabled);
	~DeathScene();

	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	virtual bool OnGuiMouseClickEvent(GuiControl* control);

	bool exitRequested;

private:

	SDL_Texture* deathTex = nullptr;
	SDL_Rect deathRect;

	Uint32 startTime = 0;
	Uint32 endTime = 0;
	Uint32 actualTime = 0;

	Font* font;
	GuiButton* buttonBackToMainMenu;
	SDL_Rect buttonBackToMainMenuRect;
	GuiButton* buttonExit;
	SDL_Rect buttonExitRect;

};



#endif __DEATH_SCENE_H__