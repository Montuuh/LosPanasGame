
#include "Module.h"
#include "List.h"
#include "SDL/include/SDL_rect.h"
#include "Textures.h"

struct SDL_Rect;


class ModuleHud: public Module
{
public:

	ModuleHud(bool isEnabled = false);
	~ModuleHud();
	//By now we will consider all modules to be permanently active
	bool Start();

	//Called at the middle of each application loop
	bool Update();

	//Called at the end of each application loop
	bool PostUpdate();

	//Called at the end of the application
	bool CleanUp();

public:
	uint score = 0;
	uint highScore = 0;
	uint previousScore = 0;

	SDL_Texture* diamondsTexture = nullptr;
	SDL_Texture* heartsTexture = nullptr;
	SDL_Texture* emptyHeartsTexture = nullptr;
	SDL_Rect spriteHearts;
	SDL_Rect spriteEmptyHearts;
	SDL_Rect spriteDiamonds;

	char scoreText[10] = { "\0" };
	char highScoreText[10] = { "\0" };
	char previousScoreText[10] = { "\0" };
	char livesText[10] = { "\0"};

	bool drawScore = true;
	
	int LevelWins = 0;
};