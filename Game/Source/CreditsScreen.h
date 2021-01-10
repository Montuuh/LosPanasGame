#ifndef __CREDITS_SCENE_H__
#define __CREDITS_SCENE_H__

#include "Module.h"
#include "GuiButton.h"

struct SDL_Rect;
class Font;

class CreditsScreen : public Module
{
public:

	CreditsScreen(bool startEnabled);
	~CreditsScreen();

	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	virtual bool OnGuiMouseClickEvent(GuiControl* control);

	bool exitRequested;

private:

	SDL_Texture* creditsTex = nullptr;
	SDL_Texture* tex = nullptr;
	SDL_Rect credits;


	Uint32 startTime = 0;
	Uint32 endTime = 0;
	Uint32 actualTime = 0;

	Font* font;
	GuiButton* buttonBack;
	SDL_Rect buttonBackRect;

};

#endif __CREDITS_SCENE_H__



