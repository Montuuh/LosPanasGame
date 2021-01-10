#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "Module.h"
#include "GuiButton.h"

struct SDL_Rect;
class Font;

class PauseScreen : public Module
{
public:

	PauseScreen(bool startEnabled);
	~PauseScreen();

	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	virtual bool OnGuiMouseClickEvent(GuiControl* control);

	bool exitRequested;

private:

	SDL_Texture* pauseTex = nullptr;
	SDL_Texture* resumeTex = nullptr;
	SDL_Texture* tex = nullptr;
	SDL_Rect pause;


	Uint32 startTime = 0;
	Uint32 endTime = 0;
	Uint32 actualTime = 0;

	Font* font;
	GuiButton* buttonResume;
	SDL_Rect buttonResumeRect;
	GuiButton* buttonExit;
	SDL_Rect buttonExitRect;
	GuiButton* buttonBackToMenu;
	SDL_Rect buttonBackToMenuRect;
	GuiButton* buttonSettings;
	SDL_Rect buttonSettingsRect;

};

#endif __PAUSE_SCENE_H__
