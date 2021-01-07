#pragma once
#ifndef __WIN_SCREEN_H__
#define __WIN_SCREEN_H__

#include "SDL/include/SDL_rect.h"

#include "Module.h"
#include "Textures.h"

struct SDL_Rect;

class WinScreen : public Module
{

public:

	WinScreen(bool startEnabled);
	~WinScreen();

	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

private:

	SDL_Texture* winTex = nullptr;
	SDL_Rect winRect;

	Uint32 startTime = 0;
	Uint32 endTime = 0;
	Uint32 actualTime = 0;

};



#endif __WIN_SCREEN_H__