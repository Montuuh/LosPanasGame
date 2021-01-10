#ifndef __WIN_SCENE_H__
#define __WIN_SCENE_H__

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

class WinScreen : public Module
{

public:

	WinScreen(bool startEnabled);
	~WinScreen();

	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	virtual bool OnGuiMouseClickEvent(GuiControl* control);

	bool exitRequested;

	uint winFx;
private:

	SDL_Texture* winTex = nullptr;
	SDL_Rect winRect;

	Uint32 startTime = 0;
	Uint32 endTime = 0;
	Uint32 actualTime = 0;

	Font* font;
	GuiButton* buttonBackToMainMenu;
	SDL_Rect buttonBackToMainMenuRect;
	GuiButton* buttonPlayAgain;
	SDL_Rect buttonPlayAgainRect;

};



#endif __WIN_SCENE_H__