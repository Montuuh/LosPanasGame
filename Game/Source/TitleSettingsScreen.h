#ifndef __TITLE_SETTINGS_SCENE_H__
#define __TITLE_SETTINGS_SCENE_H__

#include "Module.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"

struct SDL_Rect;
class Font;

class TitleSettingsScreen : public Module
{
public:

	TitleSettingsScreen(bool startEnabled);
	~TitleSettingsScreen();

	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	virtual bool OnGuiMouseClickEvent(GuiControl* control);

	bool exitRequested;

private:

	SDL_Texture* titleSettingsTex = nullptr;
	SDL_Texture* tex = nullptr;
	SDL_Rect titleSettings;

	SDL_Texture* tickTex = nullptr;

	SDL_Texture* skull = nullptr;

	Uint32 startTime = 0;
	Uint32 endTime = 0;
	Uint32 actualTime = 0;

	Font* font;
	GuiButton* buttonBack;
	SDL_Rect buttonBackRect;

	GuiSlider* musicVolume;
	GuiSlider* fxVolume;

	GuiCheckBox* checkBoxFullScreen;
	GuiCheckBox* checkBoxVsync;

};

#endif __SETTINGS_SCENE_H__


