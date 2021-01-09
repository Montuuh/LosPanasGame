#ifndef __SCENE2_H__
#define __SCENE2_H__

#include "Module.h"
#include "GuiButton.h"

struct SDL_Rect;
class Font;

class TitleScreen : public Module
{
public:

	TitleScreen(bool startEnabled);
	~TitleScreen();

	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	virtual bool OnGuiMouseClickEvent(GuiControl* control);

	bool exitRequested;

private:

	SDL_Texture* titleTex = nullptr;
	SDL_Texture* newGameTex = nullptr;
	SDL_Texture* tex = nullptr;
	SDL_Rect title;


	Uint32 startTime = 0;
	Uint32 endTime = 0;
	Uint32 actualTime = 0;

	Font* font;
	GuiButton* buttonNewGame;
	SDL_Rect buttonNewGameRect;
	GuiButton* buttonExit;
	SDL_Rect buttonExitRect;


};

#endif // __SCENE_H__