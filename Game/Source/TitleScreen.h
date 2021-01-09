#ifndef __SCENE2_H__
#define __SCENE2_H__

#include "Module.h"
#include "GuiButton.h"

struct SDL_Rect;

class TitleScreen : public Module
{
public:

	TitleScreen(bool startEnabled);
	~TitleScreen();

	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	bool OnGuiMouseClickEvent(GuiControl* control);

private:

	SDL_Texture* titleTex = nullptr;
	SDL_Texture* tex = nullptr;
	SDL_Rect title;

	Uint32 startTime = 0;
	Uint32 endTime = 0;
	Uint32 actualTime = 0;

	GuiButton* buttonNewGame;
};

#endif // __SCENE_H__